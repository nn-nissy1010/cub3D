/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:14:11 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/26 16:44:58 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// ウィンドウの×を押した時
int close_window(void *param)
{
	(void)param;
	printf("window closed.\n");
	exit(0);
	return (0);
}

int walkable(t_game *g, double x, double y)
{
    int i;
    t_object *o;

    for (i = 0; i < g->obj_count; i++)
    {
        o = g->objects[i];
        if (o->type == OBJ_WALL)
        {
            if ((int)o->x == (int)x && (int)o->y == (int)y)
                return (0);
        }
    }
    return (1);
}
t_player *get_player(t_game *g)
{
    int i;
    for (i = 0; i < g->obj_count; i++)
        if (g->objects[i]->type == OBJ_PLAYER)
            return ((t_player *)g->objects[i]);
    return (NULL);
}

int key_press(int key, t_game *g)
{
    t_player *p = get_player(g);
    double nx, ny;

    if (!p)
        return (0);

    if (key == 53) // ESC
        exit_game(g);

    nx = p->base.base.x;
    ny = p->base.base.y;

    if (key == 13) // W
        ny -= 1;
    else if (key == 1) // S
        ny += 1;
    else if (key == 0) // A
        nx -= 1;
    else if (key == 2) // D
        nx += 1;

    // 衝突判定
    if (walkable(g, nx, ny))
    {
        p->base.base.x = nx;
        p->base.base.y = ny;
    }

    // 再描画
    mlx_clear_window(g->sys.mlx, g->sys.win);
    draw_world(g);

    return (0);
}

int exit_game(t_game *g)
{
    texmgr_destroy(&g->texmgr, g->sys.mlx);

    mlx_destroy_window(g->sys.mlx, g->sys.win);
    exit(0);
    return (0);
}

void free_split(char **sp)
{
    int i;

    if (!sp)
        return;
    i = 0;
    while (sp[i])
    {
        free(sp[i]);
        i++;
    }
    free(sp);
}

void init_map(t_map *m)
{
    m->grid = NULL;
    m->height = 0;
    m->width = 0;
}

int main(int argc, char **argv)
{
    t_game g;

    if (argc != 2)
        return (printf("Usage: ./cub3D map.cub\n"), 1);
    g.obj_count = 0;
	init_map(&g.map);
    // 1. MLX
    g.sys.mlx = mlx_init();
	if (!g.sys.mlx)
	{
		printf("mlx_init failed\n");
		return (1);
	}
    g.sys.win = mlx_new_window(g.sys.mlx, 800, 600, "cub3D");
	if (!g.sys.win)
    {
        printf("mlx_new_window failed\n");
        return 1;
    }
    // 2. テクスチャ読み込み
    texmgr_init(&g.texmgr, g.sys.mlx);

    // 3. パース
    if (parse_cub(&g, argv[1]))
	{
		printf("parse failed\n");
		return (1);
	}
    // 4. 初回描画
    draw_world(&g);

    // 5. イベントフック
    mlx_hook(g.sys.win, 2, 1L<<0, key_press, &g);
    mlx_hook(g.sys.win, 17, 0, exit_game, &g);

    // 6. メインループ
    mlx_loop(g.sys.mlx);

    return (0);
}
