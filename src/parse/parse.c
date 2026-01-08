/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:33:10 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/24 12:44:29 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	read_cub_lines(t_game *g, int fd)
{
	char	*line;
	int		has_error;

	has_error = 0;
	g->map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (has_error == 0 && handle_line(g, line))
			has_error = 1;
		free(line);
	}
	if (has_error)
		return (1);
	if (!g->map_started)
	{
		printf("Error\nNo map found in .cub file\n");
		return (1);
	}
	return (0);
}

static int	finalize_map_setup(t_game *g)
{
	if (build_map_grid(&g->map))
	{
		printf("Error\nbuild_map_grid failed\n");
		return (1);
	}
	if (validate_map(&g->map))
	{
		printf("Error\nvalidate_map failed\n");
		return (1);
	}
	if (spawn_objects_from_map(g))
	{
		printf("Error\nspawn_objects_from_map failed\n");
		return (1);
	}
	return (0);
}

int	parse_cub(t_game *g, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\ncannot open cub file");
		return (1);
	}
	if (read_cub_lines(g, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (finalize_map_setup(g));
}
