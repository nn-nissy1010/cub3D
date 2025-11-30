/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:38:50 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/30 23:40:37 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_wall_cell(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	return (map->grid[y][x] == '1');
}

/*DDA ループで壁に当たるまでマップ上を進める*/
void	run_dda(t_camera *cam, t_raycalc *rc)
{
	rc->hit = 0;
	while (!rc->hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (is_wall_cell(cam->map, rc->map_x, rc->map_y))
			rc->hit = 1;
	}
}
