/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:38:02 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 19:55:59 by nnishiya         ###   ########.fr       */
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

static double direction_from_char(char c)
{
    if (c == 'N') return (3.14159265 * 1.5);
    if (c == 'S') return (3.14159265 * 0.5);
    if (c == 'W') return (3.14159265);
    if (c == 'E') return (0.0);
    return (0.0);
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
            else if (c == 'D')
            {
                add_object(g, (t_object *)new_door(px, py));
            }
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                double dir = direction_from_char(c);
                add_object(g, (t_object *)new_player(px, py, dir));
            }
            else if (c == '0')
            {
                add_object(g, (t_object *)new_structure(px, py, 0));
            }
        }
    }
    return (0);
}
