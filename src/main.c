/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:14:11 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/21 14:21:28 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_living	*find_player_living(t_game *g)
{
	int			i;
	t_object	*o;
	t_player	*p;

	i = 0;
	while (i < g->obj_count)
	{
		o = g->objects[i];
		if (o && o->type == OBJ_PLAYER)
		{
			p = (t_player *)o;
			return (&p->base);
		}
		i++;
	}
	return (NULL);
}

static void	register_mlx_hooks(t_game *g)
{
	mlx_hook(g->sys.win, 2, 1L << 0, key_press, g);
	mlx_hook(g->sys.win, 3, 1L << 1, key_release, g);
	mlx_hook(g->sys.win, 17, 0, exit_game, g);
	mlx_loop_hook(g->sys.mlx, loop_handler, g);
}

int	main(int argc, char **argv)
{
	t_game		g;
	t_living	*player;

	if (argc != 2)
		return (printf("Usage: ./cub3D map.cub\n"), 1);
	ft_bzero(&g, sizeof(t_game));
	g.obj_count = 0;
	init_game(&g);
	if (parse_cub(&g, argv[1]) != 0)
		return (printf("parse failed\n"), 1);
	player = find_player_living(&g);
	if (!player)
		return (printf("no player found in map\n"), 1);
	g.sys.mlx = mlx_init();
	if (!g.sys.mlx)
		return (printf("mlx_init failed\n"), 1);
	g.sys.win = mlx_new_window(g.sys.mlx, WIDTH, HEIGHT, "cub3D");
	if (!g.sys.win)
		return (printf("mlx_new_window failed\n"), 1);
	if (texmgr_init(&g.texmgr, g.sys.mlx) != 0)
		return (printf("texmgr_init failed\n"), 1);
	init_camera(&g.camera, player, &g.map);
	register_mlx_hooks(&g);
	mlx_loop(g.sys.mlx);
	return (0);
}
