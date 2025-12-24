/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:45:17 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/24 12:43:03 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_dda_step(t_raycalc *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
}

static void	init_ray_base(t_camera *cam, int x, t_raycalc *rc)
{
	rc->pos_x = cam->owner->base.x;
	rc->pos_y = cam->owner->base.y;
	rc->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	rc->ray_dir_x = cam->dir.dir_x + cam->dir.plane_x * rc->camera_x;
	rc->ray_dir_y = cam->dir.dir_y + cam->dir.plane_y * rc->camera_x;
	rc->map_x = (int)rc->pos_x;
	rc->map_y = (int)rc->pos_y;
	if (rc->ray_dir_x == 0)
		rc->delta_dist_x = 1e30;
	else
		rc->delta_dist_x = fabs(1.0 / rc->ray_dir_x);
	if (rc->ray_dir_y == 0)
		rc->delta_dist_y = 1e30;
	else
		rc->delta_dist_y = fabs(1.0 / rc->ray_dir_y);
}

/* x_col cam->rays[x] */
static void	cast_single_ray(t_camera *cam, int x)
{
	t_raydata	*ray;
	t_raycalc	rc;

	ray = &cam->rays[x];
	init_ray_base(cam, x, &rc);
	init_dda_step(&rc);
	run_dda(cam, &rc);
	fill_ray_result(ray, &rc);
}

/*1frame_ray*/
void	camera_cast_all_rays(t_camera *cam)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_single_ray(cam, x);
		x++;
	}
}

int	loop_handler(t_game *g)
{
	handle_input(g);
	camera_cast_all_rays(&g->camera);
	draw_world(g);
	return (0);
}
