/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:01:05 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/30 23:04:54 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

/* 壁1本ぶんのテクスチャYの進み幅(step)と初期tex_posを求める */
static t_wallparams	init_wall_params(t_game *g, int x)
{
	t_wallparams	p;
	t_raydata		*ray;
	int				h;

	ray = &g->camera.rays[x];
	h = ray->line_height;
	p.step = (double)g->texmgr.wall.height / h;
	p.tex_pos = (ray->draw_start - HEIGHT / 2 + h / 2) * p.step;
	p.y = ray->draw_start;
	if (p.y < 0)
	{
		p.tex_pos += (-p.y) * p.step;
		p.y = 0;
	}
	return (p);
}

/* x 列目の壁（縦線）を描画
	get_tex_colorで、壁を用意してから、apply_distance_shadeでshadeをつける */
static void	draw_wall_column(t_game *g, t_img *screen, int x)
{
	t_wallparams	p;
	int				tex_y;
	int				color;

	p = init_wall_params(g, x);
	while (p.y <= g->camera.rays[x].draw_end && p.y < HEIGHT)
	{
		tex_y = (int)p.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= g->texmgr.wall.height)
			tex_y = g->texmgr.wall.height - 1;
		p.tex_pos += p.step;
		color = get_tex_color(&g->texmgr.wall, g->camera.rays[x].tex_x, tex_y);
		color = apply_distance_shade(color, g->camera.rays[x].perp_dist);
		put_pixel(screen, x, p.y, color);
		p.y++;
	}
}

// 壁を貼り付ける
void	draw_walls(t_game *g, t_img *screen)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		draw_wall_column(g, screen, x);
		x++;
	}
}
