/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texmgr_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:07:02 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 23:04:42 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init_screen_img(t_texmgr *tm, void *mlx)
{
	t_img	*s;

	s = &tm->screen;
	s->width = WIDTH;
	s->height = HEIGHT;
	s->img = mlx_new_image(mlx, s->width, s->height);
	if (!s->img)
		return (1);
	s->addr = mlx_get_data_addr(s->img, &s->bpp, &s->line_len, &s->endian);
	if (!s->addr)
		return (1);
	return (0);
}

static void	load_tex(void *mlx, t_texture *out, const char *path)
{
	out->img = mlx_xpm_file_to_image(mlx, (char *)path, &out->width,
			&out->height);
	if (!out->img)
	{
		printf("Error: failed to load texture: %s\n", path);
		exit(1);
	}
}

int	texmgr_init(t_texmgr *tm, void *mlx)
{
	load_tex(mlx, &tm->wall, TEX_WALL);
	load_tex(mlx, &tm->floor, TEX_FLOOR);
	load_tex(mlx, &tm->ceiling, TEX_CEILING);
	load_tex(mlx, &tm->player, TEX_PLAYER);
	if (init_screen_img(tm, mlx))
		return (1);
	return (0);
}
