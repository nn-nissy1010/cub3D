/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:37:35 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/12 09:31:29 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	fill_void(t_map *m, char **tmp, int x, int y)
{
	if (x < 0 || y < 0 || x >= m->width || y >= m->height)
		return ;
	if (tmp[y][x] != ' ')
		return ;
	tmp[y][x] = 'V';
	fill_void(m, tmp, x + 1, y);
	fill_void(m, tmp, x - 1, y);
	fill_void(m, tmp, x, y + 1);
	fill_void(m, tmp, x, y - 1);
}

void	mark_outside_void(t_map *m, char **tmp)
{
	int	x;
	int	y;

	x = 0;
	while (x < m->width)
	{
		fill_void(m, tmp, x, 0);
		fill_void(m, tmp, x, m->height - 1);
		x++;
	}
	y = 0;
	while (y < m->height)
	{
		fill_void(m, tmp, 0, y);
		fill_void(m, tmp, m->width - 1, y);
		y++;
	}
}
