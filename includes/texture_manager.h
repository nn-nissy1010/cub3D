/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:05:26 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 19:19:30 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_H
# define TEXTURE_MANAGER_H

#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define MOVE_SPEED 0.08
#define ROT_SPEED 0.05

#define WIDTH 800
#define HEIGHT 600

#define K_ESC 65307
#define K_W 119
#define K_S 115
#define K_A 97
#define K_D 100
#define K_UP 65362
#define K_DOWN 65364
#define K_LEFT 65361
#define K_RIGHT 65363

typedef struct s_sys
{
	void		*mlx;
	void		*win;
}				t_sys;

typedef struct s_tex
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_tex;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_colors
{
	t_color		floor;
	t_color		ceiling;
}				t_colors;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_raycalc
{
	double		pos_x;
	double		pos_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
}				t_raycalc;

typedef struct s_raydata
{
	double		perp_dist;
	int			side;
	int 		step_x;
	int 		step_y;
	int			map_x;
	int			map_y;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
}				t_raydata;

/*　カメラ（プレイヤー視点）の情報　*/
typedef struct s_camera
{
	t_living	*owner;
	t_direction	dir;
	t_map		*map;

	t_raydata	rays[WIDTH];
}				t_camera;

typedef struct s_input
{
	int			forward;
	int			backward;
	int			rot_left;
	int			rot_right;
}				t_input;

typedef struct s_texture
{
	void		*img;
	int			width;
	int			height;
}				t_texture;

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

typedef struct s_texmgr
{
	t_texture	wall_north;
	t_texture	wall_south;
	t_texture	wall_west;
	t_texture	wall_east;
	t_texture	floor;
	t_texture	ceiling;
	t_texture	player;
	t_img		screen;

}				t_texmgr;

typedef struct s_game
{
	t_sys		sys;
	t_tex		tex;
	t_colors	colors;
	t_map		map;
	int			map_started;
	t_input		input;

	t_texmgr	texmgr;
	t_camera	camera;

	t_object	*objects[1024];
	int			obj_count;

}				t_game;

typedef struct s_wallparams
{
	double		step;
	double		tex_pos;
	int			y;
}				t_wallparams;

int				texmgr_init(t_game *g);
void			texmgr_destroy(t_texmgr *tm, void *mlx);

#endif
