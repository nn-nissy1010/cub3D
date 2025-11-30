/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_living.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:44:09 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 19:50:20 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	default_move(t_living *self, double dx, double dy)
{
	self->base.x += dx;
	self->base.y += dy;
}

t_living	*new_living(double x, double y)
{
	t_living	*lv;

	lv = malloc(sizeof(t_living));
	if (!lv)
		return (NULL);
	lv->base = *new_object(x, y, OBJ_LIVING, NULL);
	lv->move = &default_move;
	return (lv);
}
