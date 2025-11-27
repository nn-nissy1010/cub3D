/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:48:32 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 20:00:33 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_door *new_door(double x, double y)
{
    t_door *d;

    d = malloc(sizeof(t_door));
    if (!d)
        return (NULL);

    d->base = *new_object(x, y, OBJ_DOOR, TEX_DOOR);
    d->is_open = 0;

    return d;
}
