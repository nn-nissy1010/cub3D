/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:05:26 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 13:08:09 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_H
# define TEXTURE_MANAGER_H

typedef struct s_texture
{
    void    *img;
    int     width;
    int     height;
}   t_texture;

typedef struct s_texmgr
{
    t_texture  wall;
    t_texture  player;
    t_texture  door;
}   t_texmgr;

int  texmgr_init(t_texmgr *tm, void *mlx);
void texmgr_destroy(t_texmgr *tm, void *mlx);

#endif
