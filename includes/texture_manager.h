/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:05:26 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 23:49:42 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_H
# define TEXTURE_MANAGER_H

typedef struct s_wallparams
{
	double		step;
	double		tex_pos;
	int			y;
}				t_wallparams;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_texture
{
	void		*img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_texmgr
{
	t_texture	wall;
	t_texture	floor;
	t_texture	ceiling;
	t_texture	player;
	t_img		screen;

}				t_texmgr;

int				texmgr_init(t_texmgr *tm, void *mlx);
void			texmgr_destroy(t_texmgr *tm, void *mlx);

#endif
