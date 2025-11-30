/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:05:19 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 23:46:02 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_map(t_map *m)
{
	m->grid = NULL;
	m->height = 0;
	m->width = 0;
}

void	init_game(t_game *g)
{
	g->obj_count = 0;
	init_map(&g->map);
	g->tex.no = NULL;
	g->tex.so = NULL;
	g->tex.we = NULL;
	g->tex.ea = NULL;
	g->sys.mlx = NULL;
	g->sys.win = NULL;
}
