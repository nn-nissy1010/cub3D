/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:29:30 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/30 23:29:31 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

void	init_camera(t_camera *cam, t_living *owner, t_map *map)
{
	int	i;

	if (!cam || !owner || !map)
		return ;
	cam->owner = owner;
	cam->map = map;
	cam->dir.dir_x = owner->dir.dir_x;
	cam->dir.dir_y = owner->dir.dir_y;
	cam->dir.plane_x = -cam->dir.dir_y * 0.66;
	cam->dir.plane_y = cam->dir.dir_x * 0.66;
	i = 0;
	while (i < WIDTH)
	{
		cam->rays[i].perp_dist = 0.0;
		cam->rays[i].side = 0;
		cam->rays[i].map_x = 0;
		cam->rays[i].map_y = 0;
		cam->rays[i].wall_x = 0.0;
		cam->rays[i].line_height = 0;
		cam->rays[i].draw_start = 0;
		cam->rays[i].draw_end = 0;
		cam->rays[i].tex_x = 0;
		i++;
	}
}
