/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:48:14 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 12:50:15 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_structure *new_structure(double x, double y, int is_wall)
{
    t_structure *s;

    s = malloc(sizeof(t_structure));
    if (!s)
        return (NULL);

    s->base = *new_object(x, y, 
        is_wall ? OBJ_WALL : OBJ_STRUCTURE,
        is_wall ? TEX_WALL : NULL
    );
    s->is_wall = is_wall;

    return s;
}
