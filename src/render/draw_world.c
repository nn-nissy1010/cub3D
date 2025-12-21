/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:10:43 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 19:42:06 by tkuwahat         ###   ########.fr       */
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

/* 画面の高さ(HEIGHT)を使って、
   上半分を天井テクスチャ、下半分を床テクスチャとして切り替え、
   画面を上から1行ずつ描画していく。 */
static void	put_floor_ceiling_color(t_img *screen, int tex_color, int screen_y)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		put_pixel(screen, x, screen_y, tex_color);
		x++;
	}
}

static void	draw_floor_and_ceiling(t_game *g, t_img *screen)
{
	int		y;
	int		tex_row;
	t_color	floor_color;
	t_color	ceiling_color;
	int		tex_color;

	floor_color = g->colors.floor;
	ceiling_color = g->colors.ceiling;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
		{
			tex_color = color_to_init(ceiling_color);
			tex_row = y;
			put_floor_ceiling_color(screen, tex_color, y);
		}
		else
		{
			tex_color = color_to_init(floor_color);
			tex_row = y - HEIGHT / 2;
			put_floor_ceiling_color(screen, tex_color, y);
		}
		y++;
	}
}

void	draw_world(t_game *g)
{
	t_img	*screen;

	screen = &g->texmgr.screen;
	draw_floor_and_ceiling(g, screen);
	draw_walls(g, screen);
	mlx_put_image_to_window(g->sys.mlx, g->sys.win, screen->img, 0, 0);
}
