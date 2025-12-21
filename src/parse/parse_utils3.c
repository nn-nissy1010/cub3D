/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:33:34 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 19:22:19 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		handle_line(t_game *g, char *line);
int		handle_tex_or_color(t_game *g, char **sp);
int		add_map_line(t_game *g, char *line);

void	chop_newline(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

int	handle_line(t_game *g, char *line)
{
	char	**sp;

	chop_newline(line);
	if (is_empty(line))
		return (0);
	sp = ft_split(line, ' ');
	if (!sp)
		return (1);
	if (is_tex_id(sp[0]) || is_color_id(sp[0]))
	{
		if (g->map_started)
		{
			printf("Error\nConfiguration elements must be above the map\n");
			return (free_split(sp), 1);
		}
		if (handle_tex_or_color(g, sp))
			return (free_split(sp), 1);
		return (free_split(sp), 0);
	}
	free_split(sp);
	g->map_started = 1;
	return (add_map_line(g, line));
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
