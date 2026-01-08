/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:23 by nnishiya          #+#    #+#             */
/*   Updated: 2026/01/08 11:44:02 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	set_tex_path(char **dst, int *has_flag, char *path, char *msg)
{
	if (*has_flag)
		return (perror(msg), 1);
	*dst = ft_strdup(path);
	if (!*dst)
		return (1);
	*has_flag = 1;
	return (0);
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
	int		rgb[3];
	char	*trim;

	if (!value)
		return (1);
	trim = ft_strtrim(value, " \t\n");
	if (!trim)
		return (1);
	if (split_rgb(trim, rgb))
		return (free(trim), 1);
	free(trim);

	if (id[0] == 'F')
	{
		c->floor = (t_color){rgb[0], rgb[1], rgb[2]};
		c->has_floor = 1;
	}
	else if (id[0] == 'C')
	{
		c->ceiling = (t_color){rgb[0], rgb[1], rgb[2]};
		c->has_ceiling = 1;
	}
	else
		return (perror("invalid color id"), 1);
	return (0);
}

