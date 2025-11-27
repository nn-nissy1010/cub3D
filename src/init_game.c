/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:05:19 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/26 17:07:29 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_map(t_map *m)
{
    m->grid = NULL;
    m->height = 0;
    m->width = 0;
}

void init_game(t_game *g)
{
    g->obj_count = 0;

    // map 初期化
    init_map(&g->map);

    // テクスチャ情報は parser_cli では使わないが一応初期化
    g->tex.no = NULL;
    g->tex.so = NULL;
    g->tex.we = NULL;
    g->tex.ea = NULL;

    // MLX は parser_cli では NULL にしておく
    g->sys.mlx = NULL;
    g->sys.win = NULL;
}
