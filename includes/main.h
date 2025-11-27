/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:05 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/26 17:31:50 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "objects.h"
#include "texture.h"
#include "texture_manager.h"
#include "libft.h" 
#include "mlx.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


typedef struct s_sys
{
	void    *mlx;
	void    *win;
}   t_sys;

typedef struct s_tex
{
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
}   t_tex;

typedef struct s_color
{
	int r;
	int g;
	int b;
}   t_color;

typedef struct s_colors
{
	t_color floor;
	t_color ceiling;
}   t_colors;

typedef struct s_map
{
	char    **grid;
	int     width;
	int     height;
}   t_map;

typedef struct s_game
{
    t_sys       sys;
    t_tex       tex;
    t_colors    colors;
    t_map       map;

    t_texmgr    texmgr;

    t_object    *objects[1024];
    int         obj_count;

}   t_game;

// ------- main parse --------
int     parse_cub(t_game *g, const char *path);
void	init_game(t_game *g);

// ------- utility functions --------
int     is_empty(char *line);
int     is_tex_id(const char *id);
int     is_color_id(const char *id);

void    free_split(char **sp);

// ------- textures / colors --------
int     set_texture(t_tex *tex, char *id, char *path);
int     set_color(t_colors *c, char *id, char *value);

// ------- map builder --------
int     push_map_line(t_map *m, char *line);
int     build_map_grid(t_map *m);

// ------- map validator --------
int     validate_map(t_map *m);

// ------- objects from map --------
int     spawn_objects_from_map(t_game *g);

int		exit_game(t_game *g);
void    draw_world(t_game *g);
