/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:37:35 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 20:37:59 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse/map_validator.c

#include "main.h"

static int	is_wall(char c)
{
	return (c == '1');
}

int	validate_map(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->grid[y][x] && !ft_strchr("01NSEW ", m->grid[y][x]))
				return (1);
			if ((y == 0 || y == m->height - 1) && !is_wall(m->grid[y][x]))
				return (1);
			if ((x == 0 || x == m->width - 1) && !is_wall(m->grid[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
