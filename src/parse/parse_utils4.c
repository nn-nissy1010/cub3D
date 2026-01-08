/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:29:19 by tkuwahat          #+#    #+#             */
/*   Updated: 2026/01/08 15:32:52 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	*skip_spaces(char *s)
{
	while (*s && is_space(*s))
		s++;
	return (s);
}

int	handle_tex_or_color(t_game *g, char **sp)
{
	if (is_tex_id(sp[0]))
		return (set_texture(&g->tex, sp[0], sp[1]));
	if (is_color_id(sp[0]))
		return (set_color(&g->colors, sp[0], sp[1]));
	return (1);
}

int	add_map_line(t_game *g, char *line)
{
	return (push_map_line(&g->map, line));
}

int	set_texture(t_tex *tex, char *id, char *path)
{
	char	*trim;
	int		ret;

	if (!path)
		return (1);
	trim = ft_strtrim(path, " \t\n");
	if (!trim || !*trim)
		return (free(trim), 1);
	ret = 0;
	if (!ft_strncmp(id, "NO", 2))
		ret = set_tex_path(&tex->no, &tex->has_no, trim, "duplicate NO");
	else if (!ft_strncmp(id, "SO", 2))
		ret = set_tex_path(&tex->so, &tex->has_so, trim, "duplicate SO");
	else if (!ft_strncmp(id, "WE", 2))
		ret = set_tex_path(&tex->we, &tex->has_we, trim, "duplicate WE");
	else if (!ft_strncmp(id, "EA", 2))
		ret = set_tex_path(&tex->ea, &tex->has_ea, trim, "duplicate EA");
	else
		ret = 1;
	free(trim);
	return (ret);
}
