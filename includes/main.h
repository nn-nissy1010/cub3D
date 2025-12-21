/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:05 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 15:05:47 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "objects.h"
#include "texture.h"
#include "texture_manager.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_game
{
	t_sys		sys;
	t_tex		tex;
	t_colors	colors;
	t_map		map;
	t_input		input;

	t_texmgr	texmgr;
	t_camera	camera;

	t_object	*objects[1024];
	int			obj_count;

}				t_game;

// ------- main parse --------
int				parse_cub(t_game *g, const char *path);
void			init_game(t_game *g);
void			init_map(t_map *m);
void			chop_newline(char *s);
int				handle_line(t_game *g, char *line);
int				handle_tex_or_color(t_game *g, char **sp);
int				add_map_line(t_game *g, char *line);

// ------- utility functions --------
int				is_empty(char *line);
int				is_tex_id(const char *id);
int				is_color_id(const char *id);

void			free_split(char **sp);

// ------- textures / colors --------
int				set_texture(t_tex *tex, char *id, char *path);
int				set_color(t_colors *c, char *id, char *value);

// ------- map builder --------
int				push_map_line(t_map *m, char *line);
int				build_map_grid(t_map *m);

// ------- map validator --------
int				validate_map(t_map *m);

// ------- objects from map --------
int				spawn_objects_from_map(t_game *g);

int				exit_game(t_game *g);
void			draw_world(t_game *g);

// ------- camera --------
void			init_camera(t_camera *cam, t_living *owner, t_map *map);
void			camera_cast_all_rays(t_camera *cam);
int				loop_handler(t_game *g);
void			handle_input(t_game *g);
int				walkable(t_game *g, double x, double y);

// ------- mlx_hook --------
int				exit_game(t_game *g);
int				key_press(int key, t_game *g);
int				key_release(int key, t_game *g);

//------- draw_world --------
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_walls(t_game *g, t_img *screen);
int				apply_distance_shade(int base_color, double dist);
int				get_tex_color(t_texture *tex, int tex_x, int tex_y);

//-------- rat_result--------
void			fill_ray_result(t_raydata *ray, t_raycalc *rc);

//-------- run_dda--------
int				is_wall_cell(t_map *map, int x, int y);
void			run_dda(t_camera *cam, t_raycalc *rc);
