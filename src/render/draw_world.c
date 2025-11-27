/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:10:43 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 20:10:51 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    draw_world(t_game *g)
{
    int i;
    t_object *o;

    for (i = 0; i < g->obj_count; i++)
    {
        o = g->objects[i];

        if (o->type == OBJ_WALL)
            mlx_put_image_to_window(
                g->sys.mlx, g->sys.win,
                g->texmgr.wall.img,
                (int)(o->x * 64),
                (int)(o->y * 64)
            );
        else if (o->type == OBJ_DOOR)
            mlx_put_image_to_window(
                g->sys.mlx, g->sys.win,
                g->texmgr.door.img,
                (int)(o->x * 64),
                (int)(o->y * 64)
            );
        else if (o->type == OBJ_PLAYER)
            mlx_put_image_to_window(
                g->sys.mlx, g->sys.win,
                g->texmgr.player.img,
                (int)(o->x * 64),
                (int)(o->y * 64)
            );
    }
}
