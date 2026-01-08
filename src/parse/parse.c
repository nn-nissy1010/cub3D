/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:33:10 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/08 11:39:36 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	read_cub_lines(t_game *g, int fd)
{
	char	*line;

	g->map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (handle_line(g, line))
			return (free(line), 1);   // ★即return
		free(line);
	}
	if (!g->map_started)
		return (printf("Error\nNo map found in .cub file\n"), 1);
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

static int	validate_required_config(t_game *g)
{
	if (!g->colors.has_floor || !g->colors.has_ceiling)
		return (printf("Error\nMissing floor or ceiling color (F/C)\n"), 1);
	if (!g->tex.has_no || !g->tex.has_so || !g->tex.has_we || !g->tex.has_ea)
		return (printf("Error\nMissing texture identifier (NO/SO/WE/EA)\n"), 1);
	return (0);
}

int	parse_cub(t_game *g, const char *path)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\ncannot open cub file"), 1);

	ret = read_cub_lines(g, fd);
	close(fd);
	if (ret)
		return (1);

	if (validate_required_config(g))
		return (1);

	return (finalize_map_setup(g));
}


