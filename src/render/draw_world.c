/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:10:43 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 23:07:42 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// 距離 dist が大きいほど base_color を暗く（薄く）する
// 色が24bit(R,G,Bが8bitずつ)なので、シフト演算してから、8bit取り出して、shadeをかけてから、RGBを再合成。
int	apply_distance_shade(int base_color, double dist)
{
	double	shade;
	int		r;
	int		g;
	int		b;

	shade = 1.0 / (1.0 + dist * 0.1);
	if (shade < 0.2)
		shade = 0.2;
	r = ((base_color >> 16) & 0xFF) * shade;
	g = ((base_color >> 8) & 0xFF) * shade;
	b = (base_color & 0xFF) * shade;
	return ((r << 16) | (g << 8) | b);
}
// 指定したテクスチャの (tex_x, tex_y) の色を取得する
// テクスチャの幅(x)と高さ(y)から、ピクセルの上半分と下半分で分けて実施。

int	get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	char	*dst;

	addr = mlx_get_data_addr(tex->img, &bpp, &line_len, &endian);
	if (!addr)
		return (0);
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (0);
	dst = addr + (tex_y * line_len + tex_x * (bpp / 8));
	return (*(unsigned int *)dst);
}

/* 画面の1行（screen_y）に対して、
   テクスチャ tex の tex_row 行を左から右へ貼り付ける */
static void	draw_fc_line(t_img *screen, t_texture *tex, int screen_y,
		int tex_row)
{
	int	x;
	int	tex_x;
	int	tex_y;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		tex_x = x % tex->width;
		tex_y = tex_row % tex->height;
		color = get_tex_color(tex, tex_x, tex_y);
		put_pixel(screen, x, screen_y, color);
		x++;
	}
}

/* 画面の高さ(HEIGHT)を使って、
   上半分を天井テクスチャ、下半分を床テクスチャとして切り替え、
   画面を上から1行ずつ描画していく。 */
static void	draw_floor_and_ceiling(t_game *g, t_img *screen)
{
	int			y;
	t_texture	*ceil_tex;
	t_texture	*floor_tex;
	t_texture	*tex;
	int			tex_row;

	ceil_tex = &g->texmgr.ceiling;
	floor_tex = &g->texmgr.floor;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
		{
			tex = ceil_tex;
			tex_row = y;
		}
		else
		{
			tex = floor_tex;
			tex_row = y - HEIGHT / 2;
		}
		draw_fc_line(screen, tex, y, tex_row);
		y++;
	}
}

// 上半分（天井）と下半分（床）を描画。
// その後、真ん中を基準に壁を描画。その時にピクセル列ごとに処理。
void	draw_world(t_game *g)
{
	t_img	*screen;

	screen = &g->texmgr.screen;
	draw_floor_and_ceiling(g, screen);
	draw_walls(g, screen);
	mlx_put_image_to_window(g->sys.mlx, g->sys.win, screen->img, 0, 0);
}
