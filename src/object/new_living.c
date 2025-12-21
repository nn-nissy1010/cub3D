/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_living.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:44:09 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 14:53:52 by nnishiya         ###   ########.fr       */
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
	t_object	*obj;

	lv = malloc(sizeof(t_living));
	if (!lv)
		return (NULL);
	obj = new_object(x, y, OBJ_LIVING, NULL);
	if (!obj)
		return (free(lv), NULL);
	lv->base = *obj;
	free(obj);
	lv->move = &default_move;
	return (lv);
}
