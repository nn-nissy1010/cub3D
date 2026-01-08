/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:23 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/08 15:47:48 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_tex_path(char **dst, int *has_flag, char *path, char *msg)
{
	if (*has_flag)
		return (perror(msg), 1);
	*dst = ft_strdup(path);
	if (!*dst)
		return (1);
	*has_flag = 1;
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
			return (free(tmp), free_split(sp), perror("invalid RGB value"), 1);
		out[i] = ft_atoi(tmp);
		free(tmp);
		if (out[i] < 0 || out[i] > 255)
			return (free_split(sp), perror("RGB out of range"), 1);
		i++;
	}
	return (free_split(sp), 0);
}

void	apply_color(t_colors *c, char id, int rgb[3])
{
	if (id == 'F')
	{
		c->floor = (t_color){rgb[0], rgb[1], rgb[2]};
		c->has_floor = 1;
	}
	else if (id == 'C')
	{
		c->ceiling = (t_color){rgb[0], rgb[1], rgb[2]};
		c->has_ceiling = 1;
	}
}

int	set_color(t_colors *c, char *id, char *value)
{
	int		rgb[3];
	char	*trim;

	if (!c || !id || !value)
		return (1);
	if (!((id[0] == 'F' || id[0] == 'C') && id[1] == '\0'))
		return (perror("invalid color id"), 1);
	if (id[0] == 'F' && c->has_floor)
		return (perror("duplicate floor color"), 1);
	if (id[0] == 'C' && c->has_ceiling)
		return (perror("duplicate ceiling color"), 1);
	trim = ft_strtrim(value, " \t\n");
	if (!trim)
		return (1);
	if (split_rgb(trim, rgb))
		return (free(trim), 1);
	free(trim);
	apply_color(c, id[0], rgb);
	return (0);
}
