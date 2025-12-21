/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:24:38 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 15:05:57 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef enum e_objtype
{
	OBJ_GENERIC,
	OBJ_PLAYER,
	OBJ_LIVING,
	OBJ_STRUCTURE,
	OBJ_WALL,
	OBJ_FLOOR_CEILING
}						t_objtype;

typedef struct s_object
{
	double				x;
	double				y;
	char				*sprite_path;
	t_objtype			type;
}						t_object;

t_object				*new_object(double x, double y, t_objtype type,
							char *sprite);

typedef struct s_direction
{
	double				dir_x;
	double				dir_y;

	double				plane_x;
	double				plane_y;

}						t_direction;

typedef struct s_living	t_living;

typedef void			(*t_move_func)(t_living *self, double dx, double dy);

struct					s_living
{
	t_object			base;
	t_direction			dir;

	t_move_func			move;
};

t_living				*new_living(double x, double y);

typedef struct s_player
{
	t_living			base;
}						t_player;

t_player				*new_player(double x, double y, double dir_x,
							double dir_y);

typedef struct s_structure
{
	t_object			base;
	int					is_wall;
}						t_structure;

t_structure				*new_structure(double x, double y, int is_wall);

#endif
