/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:33:34 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/08 15:38:21 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			handle_line(t_game *g, char *line);
int			handle_tex_or_color(t_game *g, char **sp);
int			add_map_line(t_game *g, char *line);

void	chop_newline(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

static int	is_config_line(char *line)
{
	line = skip_spaces(line);
	if (!*line)
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (1);
	if ((line[0] == 'F' || line[0] == 'C') && is_space(line[1]))
		return (1);
	return (0);
}

static int	extract_id_and_value(char *line, char id[3], char **value)
{
	int		len;
	char	*p;

	line = skip_spaces(line);
	if (!*line)
		return (1);
	len = 1;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		len = 2;
	id[0] = line[0];
	id[1] = (len == 2) * line[1];
	id[2] = '\0';
	p = skip_spaces(line + len);
	*value = ft_strtrim(p, " \t\n");
	if (!*value || !**value)
		return (free(*value), *value = NULL, 1);
	return (0);
}

static int	handle_tex_or_color_line(t_game *g, char *line)
{
	char	id[3];
	char	*value;

	if (extract_id_and_value(line, id, &value))
		return (perror("invalid config line"), 1);
	if (id[0] == 'F' || id[0] == 'C')
	{
		if (set_color(&g->colors, id, value))
			return (free(value), 1);
	}
	else
	{
		if (set_texture(&g->tex, id, value))
			return (free(value), 1);
	}
	free(value);
	return (0);
}

int	handle_line(t_game *g, char *line)
{
	chop_newline(line);
	if (is_empty(line))
		return (0);
	if (is_config_line(line))
	{
		if (g->map_started)
			return (printf("Error\nConfig must come before map\n"), 1);
		return (handle_tex_or_color_line(g, line));
	}
	g->map_started = 1;
	return (add_map_line(g, line));
}
