/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:33:43 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/30 19:36:14 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	exit_game(t_game *g)
{
	texmgr_destroy(&g->texmgr, g->sys.mlx);
	mlx_destroy_window(g->sys.mlx, g->sys.win);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == 53)
		exit_game(g);
	if (key == 13 || key == 126)
		g->input.forward = 1;
	else if (key == 1 || key == 125)
		g->input.backward = 1;
	else if (key == 0 || key == 123)
		g->input.rot_left = 1;
	else if (key == 2 || key == 124)
		g->input.rot_right = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == 13 || key == 126)
		g->input.forward = 0;
	else if (key == 1 || key == 125)
		g->input.backward = 0;
	else if (key == 0 || key == 123)
		g->input.rot_left = 0;
	else if (key == 2 || key == 124)
		g->input.rot_right = 0;
	return (0);
}
