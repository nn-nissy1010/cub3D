/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:33:43 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/21 19:42:41 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_map_and_tex(t_game *g)
{
	int	i;

	free(g->tex.no);
	free(g->tex.so);
	free(g->tex.we);
	free(g->tex.ea);
	if (g->map.grid)
	{
		i = 0;
		while (i < g->map.height)
		{
			free(g->map.grid[i]);
			i++;
		}
		free(g->map.grid);
	}
}

void	free_objects(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->obj_count)
	{
		free(g->objects[i]);
		i++;
	}
}

int	exit_game(t_game *g)
{
	texmgr_destroy(&g->texmgr, g->sys.mlx);
	if (g->sys.win)
		mlx_destroy_window(g->sys.mlx, g->sys.win);
	if (g->sys.mlx)
	{
		mlx_destroy_display(g->sys.mlx);
		free(g->sys.mlx);
	}
	free_map_and_tex(g);
	free_objects(g);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == K_ESC)
		exit_game(g);
	if (key == K_W || key == K_UP)
		g->input.forward = 1;
	else if (key == K_S || key == K_DOWN)
		g->input.backward = 1;
	else if (key == K_A || key == K_LEFT)
		g->input.rot_left = 1;
	else if (key == K_D || key == K_RIGHT)
		g->input.rot_right = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == K_W || key == K_UP)
		g->input.forward = 0;
	else if (key == K_S || key == K_DOWN)
		g->input.backward = 0;
	else if (key == K_A || key == K_LEFT)
		g->input.rot_left = 0;
	else if (key == K_D || key == K_RIGHT)
		g->input.rot_right = 0;
	return (0);
}
