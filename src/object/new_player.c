/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:44:44 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 19:50:17 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_player	*new_player(double x, double y, double dir_x, double dir_y)
{
	t_player	*p;
	t_living	*living;

	living = new_living(x, y);
	if (!living)
		return (NULL);
	p = malloc(sizeof(t_player));
	if (!p)
	{
		free(living);
		return (NULL);
	}
	p->base = *living;
	free(living);
	p->base.base.type = OBJ_PLAYER;
	p->base.base.sprite_path = TEX_PLAYER;
	p->base.dir.dir_x = dir_x;
	p->base.dir.dir_y = dir_y;
	p->base.dir.plane_x = -dir_y * 0.66;
	p->base.dir.plane_y = dir_x * 0.66;
	return (p);
}
