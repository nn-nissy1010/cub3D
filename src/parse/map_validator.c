/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:37:35 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 20:30:46 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse/map_validator.c

#include "main.h"

static int is_wall(char c)
{
    return (c == '1');
}

int validate_map(t_map *m)
{
    int y, x;

    // 上下が全部壁か確認
    for (x = 0; x < m->width; x++)
    {
        if (!is_wall(m->grid[0][x]) || !is_wall(m->grid[m->height - 1][x]))
            return (perror("map not closed"), 1);
    }
    // 左右壁チェック
    for (y = 0; y < m->height; y++)
    {
        if (!is_wall(m->grid[y][0]) || !is_wall(m->grid[y][m->width - 1]))
            return (perror("map not closed"), 1);
    }
    return (0);
}
