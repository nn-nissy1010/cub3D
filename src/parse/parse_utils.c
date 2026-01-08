/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/24 12:48:29 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_texture(t_tex *tex, char *id, char *path)
{
	if (!path)
		return (perror("missing texture path"), 1);
	if (!ft_strncmp(id, "NO", 2))
		tex->no = ft_strdup(path);
	else if (!ft_strncmp(id, "SO", 2))
		tex->so = ft_strdup(path);
	else if (!ft_strncmp(id, "WE", 2))
		tex->we = ft_strdup(path);
	else if (!ft_strncmp(id, "EA", 2))
		tex->ea = ft_strdup(path);
	else
		return (perror("invalid texture id"), 1);
	return (0);
}

static int	split_rgb(char *str, int out[3])
{
	char	**sp;
	int		i;

	sp = ft_split(str, ',');
	if (!sp)
		return (1);
	i = 0;
	while (sp[i])
		i++;
	if (i != 3)
		return (free_split(sp), perror("invalid RGB"), 1);
	out[0] = ft_atoi(sp[0]);
	out[1] = ft_atoi(sp[1]);
	out[2] = ft_atoi(sp[2]);
	free_split(sp);
	return (0);
}

int	set_color(t_colors *c, char *id, char *value)
{
	int	rgb[3];

	if (!value || split_rgb(value, rgb))
		return (1);
	if (id[0] == 'F')
		c->floor = (t_color){rgb[0], rgb[1], rgb[2]};
	else if (id[0] == 'C')
		c->ceiling = (t_color){rgb[0], rgb[1], rgb[2]};
	else
		return (perror("invalid color id"), 1);
	return (0);
}
