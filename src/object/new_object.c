/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:43:10 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 19:50:17 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_object	*new_object(double x, double y, t_objtype type, char *sprite)
{
	t_object	*o;

	o = malloc(sizeof(t_object));
	if (!o)
		return (NULL);
	o->x = x;
	o->y = y;
	o->type = type;
	o->sprite_path = sprite;
	return (o);
}
