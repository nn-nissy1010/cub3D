/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:23 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/08 11:13:12 by tkuwahat         ###   ########.fr       */
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

static int	is_valid_rgb(char *s)
{
	int	i;

	if (!*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	split_rgb(char *str, int out[3])
{
	char	**sp;
	char	*tmp;
	int		i;

	sp = ft_split(str, ',');
	if (!sp)
		return (1);

	i = 0;
	while (sp[i])
		i++;
	if (i != 3)
		return (free_split(sp), perror("invalid RGB"), 1);

	i = 0;
	while (i < 3)
	{
		tmp = ft_strtrim(sp[i], " \t\n");
		if (!tmp || !is_valid_rgb(tmp))
			return (free(tmp), free_split(sp),
				perror("invalid RGB value"), 1);
		out[i] = ft_atoi(tmp);
		free(tmp);
		if (out[i] < 0 || out[i] > 255)
			return (free_split(sp),
				perror("RGB out of range"), 1);
		i++;
	}
	free_split(sp);
	return (0);
}

int	set_color(t_colors *c, char *id, char *value)
{
	int	rgb[3];

	printf("%s", value);
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
