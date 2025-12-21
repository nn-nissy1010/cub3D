/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:01:05 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/21 18:55:48 by nnishiya         ###   ########.fr       */
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

static t_wallparams	init_wall_params(t_game *g, int x, t_texture *tex)
{
	t_wallparams	p;
	t_raydata		*ray;
	int				h;

	ray = &g->camera.rays[x];
	h = ray->line_height;
	p.step = (double)tex->height / h;
	p.tex_pos = (ray->draw_start - HEIGHT / 2 + h / 2) * p.step;
	p.y = ray->draw_start;
	if (p.y < 0)
	{
		p.tex_pos += (-p.y) * p.step;
		p.y = 0;
	}
	return (p);
}

static t_texture	*prepare_tex(t_game *g, t_raydata *ray, int *tex_x)
{
	t_texture	*tex;

	if (ray->side == 0 && ray->step_x > 0)
		tex = &g->texmgr.wall_west;
	else if (ray->side == 0)
		tex = &g->texmgr.wall_east;
	else if (ray->step_y > 0)
		tex = &g->texmgr.wall_north;
	else
		tex = &g->texmgr.wall_south;
	*tex_x = (int)(ray->wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->step_x > 0) || (ray->side == 1
			&& ray->step_y < 0))
		*tex_x = tex->width - *tex_x - 1;
	if (*tex_x >= tex->width)
		*tex_x = tex->width - 1;
	else if (*tex_x < 0)
		*tex_x = 0;
	return (tex);
}

static void	draw_wall_column(t_game *g, t_img *screen, int x)
{
	t_wallparams	p;
	t_raydata		*ray;
	t_texture		*tex;
	int				tex_x;
	int				tex_y;

	ray = &g->camera.rays[x];
	tex = prepare_tex(g, ray, &tex_x);
	p = init_wall_params(g, x, tex);
	while (p.y <= ray->draw_end && p.y < HEIGHT)
	{
		tex_y = (int)p.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		p.tex_pos += p.step;
		put_pixel(screen, x, p.y, apply_distance_shade(get_tex_color(tex, tex_x,
					tex_y), ray->perp_dist));
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
