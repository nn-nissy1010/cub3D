/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:38:02 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 21:29:06 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse/spawn_objects.c

#include "main.h"

static void add_object(t_game *g, t_object *obj)
{
    if (g->obj_count >= 1024)
        return; // 一応保護。error() してもよし。
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


int spawn_objects_from_map(t_game *g)
{
    int y, x;

    for (y = 0; y < g->map.height; y++)
    {
        for (x = 0; x < g->map.width; x++)
        {
            char c = g->map.grid[y][x];
            double px = x + 0.5;
            double py = y + 0.5;

            if (c == '1')
            {
                add_object(g, (t_object *)new_structure(px, py, 1));  // 壁
            }
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                double dir_x;
                double dir_y;
                dir_from_char(c, &dir_x, &dir_y);
                add_object(g, (t_object *)new_player(px, py, dir_x, dir_y));
            }
            else if (c == '0')
            {
                add_object(g, (t_object *)new_structure(px, py, 0));
            }
        }
    }
    return (0);
}
