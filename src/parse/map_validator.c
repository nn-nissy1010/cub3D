/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:37:35 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 19:43:29 by nnishiya         ###   ########.fr       */
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

	x = 0;
	while (x < m->width)
	{
		if (!is_wall(m->grid[0][x]) || !is_wall(m->grid[m->height - 1][x]))
		{
			perror("Error\nmap not closed");
			return (1);
		}
		x++;
	}
	y = 0;
	while (y < m->height)
	{
		if (!is_wall(m->grid[y][0]) || !is_wall(m->grid[y][m->width - 1]))
		{
			perror("Error\nmap not closed");
			return (1);
		}
		y++;
	}
	return (0);
}
