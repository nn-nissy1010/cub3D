/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_living.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:44:09 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 19:44:17 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void default_move(t_living *self, double dx, double dy)
{
    self->base.x += dx;
    self->base.y += dy;
}

static void default_attack(t_living *self, t_living *target)
{
    if (!target)
        return;
    target->hp -= (self->attack - target->defense);
}

t_living *new_living(double x, double y)
{
    t_living *lv;

    lv = malloc(sizeof(t_living));
    if (!lv)
        return (NULL);

    lv->base = *new_object(x, y, OBJ_LIVING, NULL);

    lv->hp = 100;
    lv->attack = 10;
    lv->defense = 5;

    lv->move = &default_move;
    lv->do_attack = &default_attack;

    return lv;
}
