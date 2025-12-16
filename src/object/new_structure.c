/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:48:14 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 19:51:56 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_structure	*new_structure(double x, double y, int is_wall)
{
	t_structure	*s;
	t_object	*obj;

	s = malloc(sizeof(t_structure));
	if (!s)
		return (NULL);
	if (is_wall)
		obj = new_object(x, y, OBJ_WALL, TEX_WALL);
	else
		obj = new_object(x, y, OBJ_STRUCTURE, NULL);
	s->base = *obj;
	s->is_wall = is_wall;
	return (s);
}
