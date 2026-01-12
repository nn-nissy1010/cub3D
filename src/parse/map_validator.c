/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:37:35 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/12 09:26:26 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	free_grid(char **g)
{
	int	i;

	if (!g)
		return ;
	i = 0;
	while (g[i])
		free(g[i++]);
	free(g);
}

static char	**dup_grid(t_map *m)
{
	char	**tmp;
	int		y;

	tmp = malloc(sizeof(char *) * (m->height + 1));
	if (!tmp)
		return (NULL);
	y = 0;
	while (y < m->height)
	{
		tmp[y] = ft_strdup(m->grid[y]);
		if (!tmp[y])
			return (free_grid(tmp), NULL);
		y++;
	}
	tmp[y] = NULL;
	return (tmp);
}

static int	touches_marked_void(char **tmp, int x, int y)
{
	return (tmp[y - 1][x] == 'V' || tmp[y + 1][x] == 'V' || tmp[y][x - 1] == 'V'
		|| tmp[y][x + 1] == 'V');
}

static int	validate_cell(t_map *m, char **tmp, int x, int y)
{
	char	c;

	c = m->grid[y][x];
	if (!ft_strchr("01NSEW ", c))
		return (1);
	if (is_walkable(c))
	{
		if (y == 0 || x == 0 || y == m->height - 1 || x == m->width - 1)
			return (1);
		if (touches_marked_void(tmp, x, y))
			return (1);
	}
	return (0);
}

int	validate_map(t_map *m)
{
	int		x;
	int		y;
	char	**tmp;

	tmp = dup_grid(m);
	if (!tmp)
		return (1);
	mark_outside_void(m, tmp);
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (validate_cell(m, tmp, x, y))
				return (free_grid(tmp), 1);
			x++;
		}
		y++;
	}
	return (free_grid(tmp), 0);
}
