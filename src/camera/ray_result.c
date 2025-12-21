/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_result.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:34:05 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/21 20:26:42 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

static void	set_perp_dist_and_basic(t_raydata *ray, t_raycalc *rc)
{
	if (rc->side == 0)
		ray->perp_dist = (rc->map_x - rc->pos_x + (1 - rc->step_x) / 2.0)
			/ rc->ray_dir_x;
	else
		ray->perp_dist = (rc->map_y - rc->pos_y + (1 - rc->step_y) / 2.0)
			/ rc->ray_dir_y;
	ray->side = rc->side;
	ray->map_x = rc->map_x;
	ray->map_y = rc->map_y;
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
}

static void	set_draw_range(t_raydata *ray)
{
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	set_wall_hit_and_tex(t_raydata *ray, t_raycalc *rc)
{
	ray->side = rc->side;
	ray->step_x = rc->step_x;
	ray->step_y = rc->step_y;
	if (rc->side == 0)
		ray->wall_x = rc->pos_y + ray->perp_dist * rc->ray_dir_y;
	else
		ray->wall_x = rc->pos_x + ray->perp_dist * rc->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

void	fill_ray_result(t_raydata *ray, t_raycalc *rc)
{
	set_perp_dist_and_basic(ray, rc);
	set_draw_range(ray);
	set_wall_hit_and_tex(ray, rc);
}
