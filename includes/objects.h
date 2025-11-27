/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:24:38 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/25 19:53:10 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

/*
** ===========================================
**  Object 系の最上位抽象クラス
** ===========================================
*/

typedef enum e_objtype {
    OBJ_GENERIC,
    OBJ_LIVING,
    OBJ_PLAYER,
    OBJ_ENEMY,
    OBJ_ITEM,
    OBJ_DOOR,
    OBJ_STRUCTURE,
    OBJ_WALL,
    OBJ_FLOOR_CEILING
}   t_objtype;

typedef struct s_object
{
    double      x;
    double      y;
    char        *sprite_path;
    t_objtype   type;
}   t_object;

t_object *new_object(double x, double y, t_objtype type, char *sprite);


/*
** ===========================================
**  LivingThing（生き物）
** ===========================================
*/

typedef struct s_living  t_living;

typedef void (*t_move_func)(t_living *self, double dx, double dy);
typedef void (*t_attack_func)(t_living *self, t_living *target);

struct s_living
{
    t_object        base;       // ← Object 継承
    int             hp;
    int             attack;
    int             defense;

    t_move_func     move;
    t_attack_func   do_attack;
};

t_living *new_living(double x, double y);

/*
** ===========================================
**  Player
** ===========================================
*/

typedef struct s_player
{
    t_living    base;
    double      direction;       // ラジアン
    void        (*open_door)(struct s_player *self);
}   t_player;

t_player *new_player(double x, double y, double dir);

/*
** ===========================================
**  Enemy
** ===========================================
*/

typedef struct s_enemy
{
    t_living    base;
    int         ai_type;
}   t_enemy;


/*
** ===========================================
**  Item
** ===========================================
*/

typedef struct s_item
{
    t_object    base;
    void        (*effect)(struct s_item *self, t_living *target);
}   t_item;

typedef struct s_food
{
    t_item      base;
}   t_food;

typedef struct s_armor
{
    t_item      base;
    int         defense_bonus;
}   t_armor;

typedef struct s_weapon
{
    t_item      base;
    int         attack_bonus;
}   t_weapon;


/*
** ===========================================
**  Door
** ===========================================
*/

typedef struct s_door
{
    t_object    base;
    int         is_open;
}   t_door;

t_door *new_door(double x, double y);

/*
** ===========================================
**  Structure（構造物）
** ===========================================
*/

typedef struct s_structure
{
    t_object    base;
    int         is_wall;
}   t_structure;

t_structure *new_structure(double x, double y, int is_wall);

#endif
