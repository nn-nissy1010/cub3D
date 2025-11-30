/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:16:12 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/30 23:29:16 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	walkable(t_game *g, double x, double y)
{
	int			i;
	t_object	*o;

	i = 0;
	while (i < g->obj_count)
	{
		o = g->objects[i];
		if (o->type == OBJ_WALL)
		{
			if ((int)o->x == (int)x && (int)o->y == (int)y)
				return (0);
		}
		i++;
	}
	return (1);
}

static void	handle_move(t_game *g, t_living *pl)
{
	double	nx;
	double	ny;

	nx = pl->base.x;
	ny = pl->base.y;
	if (g->input.forward)
	{
		nx += pl->dir.dir_x * MOVE_SPEED;
		ny += pl->dir.dir_y * MOVE_SPEED;
	}
	if (g->input.backward)
	{
		nx -= pl->dir.dir_x * MOVE_SPEED;
		ny -= pl->dir.dir_y * MOVE_SPEED;
	}
	if (walkable(g, nx, ny))
	{
		pl->base.x = nx;
		pl->base.y = ny;
	}
}

static void	handle_rotate(t_game *g, t_living *pl)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = 0.0;
	if (g->input.rot_left)
		angle = -ROT_SPEED;
	else if (g->input.rot_right)
		angle = ROT_SPEED;
	if (angle == 0.0)
		return ;
	old_dir_x = pl->dir.dir_x;
	old_plane_x = pl->dir.plane_x;
	pl->dir.dir_x = pl->dir.dir_x * cos(angle) - pl->dir.dir_y * sin(angle);
	pl->dir.dir_y = old_dir_x * sin(angle) + pl->dir.dir_y * cos(angle);
	pl->dir.plane_x = pl->dir.plane_x * cos(angle) - pl->dir.plane_y
		* sin(angle);
	pl->dir.plane_y = old_plane_x * sin(angle) + pl->dir.plane_y * cos(angle);
}

void	handle_input(t_game *g)
{
	t_living	*pl;

	pl = g->camera.owner;
	if (!pl)
		return ;
	handle_move(g, pl);
	handle_rotate(g, pl);
	g->camera.dir = pl->dir;
}
