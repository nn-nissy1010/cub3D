/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:38:02 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 14:28:18 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse/spawn_objects.c

#include "main.h"

static void	add_object(t_game *g, t_object *obj)
{
	if (g->obj_count >= 1024)
		return ;
	g->objects[g->obj_count++] = obj;
}

static void	dir_from_char(char c, double *dx, double *dy)
{
	if (c == 'N')
	{
		*dx = 0.0;
		*dy = -1.0;
	}
	else if (c == 'S')
	{
		*dx = 0.0;
		*dy = 1.0;
	}
	else if (c == 'E')
	{
		*dx = 1.0;
		*dy = 0.0;
	}
	else
	{
		*dx = -1.0;
		*dy = 0.0;
	}
}

static void	spawn_at_pos(t_game *g, char c, int x, int y)
{
	double	dir_x;
	double	dir_y;

	if (c == '1')
		add_object(g, (t_object *)new_structure(x + 0.5, y + 0.5, 1));
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		dir_from_char(c, &dir_x, &dir_y);
		add_object(g, (t_object *)new_player(x + 0.5, y + 0.5, dir_x, dir_y));
	}
	else if (c == '0')
		add_object(g, (t_object *)new_structure(x + 0.5, y + 0.5, 0));
}

int	spawn_objects_from_map(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			spawn_at_pos(g, g->map.grid[y][x], x, y);
			x++;
		}
		y++;
	}
	return (0);
}
