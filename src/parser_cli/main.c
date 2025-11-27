/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:58:17 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/26 17:30:08 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void print_json_map(const t_map *m)
{
    printf("  \"map\": [\n");
    for (int y = 0; y < m->height; y++)
    {
        printf("    \"%s\"", m->grid[y]);
        if (y + 1 < m->height)
            printf(",");
        printf("\n");
    }
    printf("  ],\n");

    printf("  \"width\": %d,\n", m->width);
    printf("  \"height\": %d,\n", m->height);
}

static void print_json_colors(const t_colors *c)
{
    printf("  \"colors\": {\n");
    printf("    \"floor\": [%d, %d, %d],\n",
        c->floor.r, c->floor.g, c->floor.b);
    printf("    \"ceiling\": [%d, %d, %d]\n",
        c->ceiling.r, c->ceiling.g, c->ceiling.b);
    printf("  },\n");
}

static void print_json_textures(const t_tex *t)
{
    printf("  \"textures\": {\n");
    printf("    \"NO\": \"%s\",\n", t->no);
    printf("    \"SO\": \"%s\",\n", t->so);
    printf("    \"WE\": \"%s\",\n", t->we);
    printf("    \"EA\": \"%s\"\n", t->ea);
    printf("  },\n");
}

static const char *objtype_to_str(t_objtype t)
{
    if (t == OBJ_PLAYER) return "player";
    if (t == OBJ_WALL) return "wall";
    if (t == OBJ_DOOR) return "door";
    if (t == OBJ_STRUCTURE) return "structure";
    if (t == OBJ_LIVING) return "living";
    if (t == OBJ_ITEM) return "item";
    return "object";
}

static void print_json_objects(const t_game *g)
{
    printf("  \"objects\": [\n");
    for (int i = 0; i < g->obj_count; i++)
    {
        t_object *o = g->objects[i];

        printf("    {\n");
        printf("      \"type\": \"%s\",\n", objtype_to_str(o->type));
        printf("      \"x\": %.2f,\n", o->x);
        printf("      \"y\": %.2f,\n", o->y);

        // プレイヤー専用情報
        if (o->type == OBJ_PLAYER)
        {
            t_player *p = (t_player *)o;
            printf("      \"direction\": %.2f\n", p->direction);
        }
        else
        {
            printf("      \"sprite\": \"%s\"\n",
                o->sprite_path ? o->sprite_path : "");
        }

        if (i + 1 < g->obj_count)
            printf("    },\n");
        else
            printf("    }\n");
    }
    printf("  ]\n");
}

void print_json(const t_game *g)
{
    printf("{\n");

    print_json_map(&g->map);
    print_json_colors(&g->colors);
    print_json_textures(&g->tex);
    print_json_objects(g);

    printf("}\n");
}

int main(int argc, char **argv)
{
    t_game g;

    if (argc != 2)
        return (printf("Usage: ./parser_cli map.cub\n"), 1);

    init_game(&g);

    if (parse_cub(&g, argv[1]))
    {
        printf("{ \"error\": \"parse failed\" }\n");
        return (1);
    }

    print_json(&g);
    return (0);
}
