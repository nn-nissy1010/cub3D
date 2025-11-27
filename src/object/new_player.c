/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:44:44 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 20:04:33 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void default_open_door(t_player *self)
{
    (void)self;
    // 実装はゲームロジック側で
}

t_player *new_player(double x, double y, double dir)
{
    t_player *p;

    p = malloc(sizeof(t_player));
    if (!p)
        return (NULL);

    p->base = *new_living(x, y);
    p->base.base.type = OBJ_PLAYER;
    p->base.base.sprite_path = TEX_PLAYER;

    p->direction = dir;
    p->open_door = &default_open_door;

    return p;
}
