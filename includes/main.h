/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:05 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 21:37:34 by nnishiya         ###   ########.fr       */
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

// ------- main parse --------
int		parse_cub(t_game *g, const char *path);
void	init_game(t_game *g);
void	init_map(t_map *m);
void	chop_newline(char *s);
int		handle_line(t_game *g, char *line);
int		handle_tex_or_color(t_game *g, char **sp);
int		add_map_line(t_game *g, char *line);

// ------- utility functions --------
int		is_empty(char *line);
int		is_tex_id(const char *id);
int		is_color_id(const char *id);

void	free_split(char **sp);

// ------- textures / colors --------
int		set_texture(t_tex *tex, char *id, char *path);
int		set_color(t_colors *c, char *id, char *value);
int		color_to_init(t_color c);

// ------- map builder --------
int		push_map_line(t_map *m, char *line);
int		build_map_grid(t_map *m);

// ------- map validator --------
int		validate_map(t_map *m);
void	free_map_and_tex(t_game *g);
void	free_objects(t_game *g);

// ------- objects from map --------
int		spawn_objects_from_map(t_game *g);

int		exit_game(t_game *g);
void	draw_world(t_game *g);

// ------- camera --------
void	init_camera(t_camera *cam, t_living *owner, t_map *map);
void	camera_cast_all_rays(t_camera *cam);
int		loop_handler(t_game *g);
void	handle_input(t_game *g);
int		walkable(t_game *g, double x, double y);

// ------- mlx_hook --------
int		exit_game(t_game *g);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);

//------- draw_world --------
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_walls(t_game *g, t_img *screen);
int		apply_distance_shade(int base_color, double dist);
int		get_tex_color(t_texture *tex, int tex_x, int tex_y);

//-------- rat_result--------
void	fill_ray_result(t_raydata *ray, t_raycalc *rc);

//-------- run_dda--------
int		is_wall_cell(t_map *map, int x, int y);
void	run_dda(t_camera *cam, t_raycalc *rc);
