/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:14:11 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/12/21 20:39:39 by nnishiya         ###   ########.fr       */
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

int	exit_error(t_game *g, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	free_map_and_tex(g);
	free_objects(g);
	if (g->sys.mlx)
	{
		texmgr_destroy(&g->texmgr, g->sys.mlx);
		if (g->sys.win)
			mlx_destroy_window(g->sys.mlx, g->sys.win);
		mlx_destroy_display(g->sys.mlx);
		free(g->sys.mlx);
	}
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game		g;
	t_living	*player;

	if (argc != 2)
		exit_error(&g, "Usage: ./cub3D map.cub\n");
	ft_bzero(&g, sizeof(t_game));
	g.obj_count = 0;
	init_game(&g);
	if (parse_cub(&g, argv[1]) != 0)
		exit_error(&g, "parse failed\n");
	player = find_player_living(&g);
	if (!player)
		exit_error(&g, "no player found in map\n");
	g.sys.mlx = mlx_init();
	if (!g.sys.mlx)
		exit_error(&g, "mlx_init failed\n");
	g.sys.win = mlx_new_window(g.sys.mlx, WIDTH, HEIGHT, "cub3D");
	if (!g.sys.win)
		exit_error(&g, "mlx_new_window failed\n");
	if (texmgr_init(&g) != 0)
		exit_error(&g, "texmgr_init failed\n");
	init_camera(&g.camera, player, &g.map);
	register_mlx_hooks(&g);
	mlx_loop(g.sys.mlx);
	return (0);
}
