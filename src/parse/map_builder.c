/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:36:57 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 12:54:09 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse/map_builder.c

#include "main.h"

int push_map_line(t_map *m, char *line)
{
    char **new_grid;
    int    i;

    new_grid = malloc(sizeof(char *) * (m->height + 2));
    if (!new_grid)
        return (1);

    i = 0;
    while (i < m->height)
    {
        new_grid[i] = m->grid[i];
        i++;
    }
    new_grid[i] = ft_strdup(line);
    new_grid[i + 1] = NULL;

    if (m->grid)
        free(m->grid);
    m->grid = new_grid;
    m->height++;

    return (0);
}

int build_map_grid(t_map *m)
{
    int  i, j;

    // 幅を決める（最大長）
    m->width = 0;
    for (i = 0; i < m->height; i++)
    {
        int len = ft_strlen(m->grid[i]);
        if (len > m->width)
            m->width = len;
    }

    // 各行を width に揃える
    for (i = 0; i < m->height; i++)
    {
        int len = ft_strlen(m->grid[i]);
        if (len < m->width)
        {
            char *new = malloc(m->width + 1);
            if (!new) 
                return (1);

            // 元行コピー
            for (j = 0; j < len; j++)
                new[j] = m->grid[i][j];

            // 足りない部分は「壁」で埋める
            for (j = len; j < m->width; j++)
                new[j] = '1';   // ←←← ここが重要 !!!

            new[m->width] = '\0';

            free(m->grid[i]);
            m->grid[i] = new;
        }
    }
    return (0);
}
