/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:57 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/12 08:49:53 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	push_map_line(t_map *m, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (m->height + 2));
	if (!new_grid)
		return (1);
	i = 0;
	while (i < m->height)
	{
		new_grid[i] = m->grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(line);
	new_grid[i + 1] = NULL;
	if (m->grid)
		free(m->grid);
	m->grid = new_grid;
	m->height++;
	return (0);
}

static int	pad_line(char **line, int width)
{
	char	*new;
	int		len;
	int		j;

	len = ft_strlen(*line);
	if (len >= width)
		return (0);
	new = malloc(sizeof(char) * (width + 1));
	if (!new)
		return (1);
	j = 0;
	while (j < len)
	{
		new[j] = (*line)[j];
		j++;
	}
	while (j < width)
		new[j++] = ' ';
	new[j] = '\0';
	free(*line);
	*line = new;
	return (0);
}

static void	set_max_width(t_map *m)
{
	int	i;
	int	len;

	i = 0;
	m->width = 0;
	while (i < m->height)
	{
		len = ft_strlen(m->grid[i]);
		if (len > m->width)
			m->width = len;
		i++;
	}
}

int	build_map_grid(t_map *m)
{
	int	i;

	set_max_width(m);
	i = 0;
	while (i < m->height)
	{
		if (pad_line(&m->grid[i], m->width))
			return (1);
		i++;
	}
	return (0);
}
