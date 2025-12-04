/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texmgr_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:07:02 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 13:08:01 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void load_tex(void *mlx, t_texture *out, const char *path)
{
    out->img = mlx_xpm_file_to_image(
        mlx, (char *)path, &out->width, &out->height
    );
    if (!out->img)
    {
        printf("Error: failed to load texture: %s\n", path);
        exit(1);
    }
}

int texmgr_init(t_texmgr *tm, void *mlx)
{
    load_tex(mlx, &tm->wall,    TEX_WALL);
    load_tex(mlx, &tm->player,  TEX_PLAYER);
    load_tex(mlx, &tm->door,    TEX_DOOR);

    return (0);
}
