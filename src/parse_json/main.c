/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:15:28 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 15:20:23 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* ===== forward declarations ===== */

static void skip_spaces(char *s, int *i);
static char *parse_string(char *s, int *i);
static double parse_number(char *s, int *i);
static void expect(char *s, int *i, char c);

static void parse_colors(t_game *g, char *s, int *i);
static void parse_textures(t_game *g, char *s, int *i);
static void parse_map(t_game *g, char *s, int *i);

static void parse_one_object(t_game *g, char *s, int *i);
static void parse_objects(t_game *g, char *s, int *i);

static char *read_all(char *path);
// static void parse_game_json(t_game *g, char *path);

/*
** ============================
** Utils
** ============================
*/

static void skip_spaces(char *s, int *i)
{
    while (s[*i] == ' ' || s[*i] == '\n' || s[*i] == '\t' || s[*i] == '\r')
        (*i)++;
}

static char *parse_string(char *s, int *i)
{
    int start;
    int len;
    char *out;

    skip_spaces(s, i);
    if (s[*i] != '"')
        return (NULL);
    (*i)++;
    start = *i;
    while (s[*i] && s[*i] != '"')
        (*i)++;
    len = *i - start;
    out = malloc(len + 1);
    memcpy(out, s + start, len);
    out[len] = '\0';
    (*i)++;
    return (out);
}

static double parse_number(char *s, int *i)
{
    double num;
    skip_spaces(s, i);
    num = atof(&s[*i]);
    while ((s[*i] >= '0' && s[*i] <= '9') || s[*i] == '.' || s[*i] == '-')
        (*i)++;
    return (num);
}

static void expect(char *s, int *i, char c)
{
    skip_spaces(s, i);
    if (s[*i] != c)
    {
        write(2, "JSON error\n", 11);
        exit(1);
    }
    (*i)++;
}

/*
** ============================
** Parse Colors
** ============================
*/

static void parse_color_array(t_color *c, char *s, int *i)
{
    expect(s, i, '[');
    c->r = (int)parse_number(s, i);
    expect(s, i, ',');
    c->g = (int)parse_number(s, i);
    expect(s, i, ',');
    c->b = (int)parse_number(s, i);
    expect(s, i, ']');
}

static void parse_colors(t_game *g, char *s, int *i)
{
    expect(s, i, '{');

    while (1)
    {
        char *key = parse_string(s, i);
        expect(s, i, ':');

        if (!strcmp(key, "floor"))
            parse_color_array(&g->colors.floor, s, i);
        else if (!strcmp(key, "ceiling"))
            parse_color_array(&g->colors.ceiling, s, i);

        free(key);

        skip_spaces(s, i);
        if (s[*i] == '}')
            break;
        expect(s, i, ',');
    }
    expect(s, i, '}');
}

/*
** ============================
** Parse Textures
** ============================
*/

static void parse_textures(t_game *g, char *s, int *i)
{
    expect(s, i, '{');

    while (1)
    {
        char *key = parse_string(s, i);
        expect(s, i, ':');
        char *val = parse_string(s, i);

        if (!strcmp(key, "NO"))
            g->tex.no = val;
        else if (!strcmp(key, "SO"))
            g->tex.so = val;
        else if (!strcmp(key, "WE"))
            g->tex.we = val;
        else if (!strcmp(key, "EA"))
            g->tex.ea = val;
        else
            free(val);

        free(key);

        skip_spaces(s, i);
        if (s[*i] == '}')
            break;
        expect(s, i, ',');
    }
    expect(s, i, '}');
}

/*
** ============================
** Parse Map
** ============================
*/

static void parse_map(t_game *g, char *s, int *i)
{
    int tmp;
    int size = 0;
    int idx = 0;

    expect(s, i, '[');

    tmp = *i;
    while (1)
    {
        skip_spaces(s, &tmp);
        if (s[tmp] == '"')
            size++;
        while (s[tmp] && s[tmp] != ',' && s[tmp] != ']')
            tmp++;
        if (s[tmp] == ']')
            break;
        tmp++;
    }

    g->map.grid = malloc(sizeof(char *) * (size + 1));

    while (1)
    {
        skip_spaces(s, i);
        if (s[*i] == ']')
            break;

        g->map.grid[idx++] = parse_string(s, i);

        skip_spaces(s, i);
        if (s[*i] == ',')
            (*i)++;
    }

    g->map.grid[idx] = NULL;
    expect(s, i, ']');

    g->map.height = size;
    g->map.width = strlen(g->map.grid[0]);
}

/*
** ============================
** Parse Objects
** ============================
*/

static t_objtype parse_obj_type(char *s)
{
    if (!strcmp(s, "player")) return OBJ_PLAYER;
    if (!strcmp(s, "enemy")) return OBJ_ENEMY;
    if (!strcmp(s, "item")) return OBJ_ITEM;
    if (!strcmp(s, "door")) return OBJ_DOOR;
    if (!strcmp(s, "structure")) return OBJ_STRUCTURE;
    if (!strcmp(s, "wall")) return OBJ_WALL;
    return OBJ_GENERIC;
}

static void parse_objects(t_game *g, char *s, int *i)
{
    expect(s, i, '[');

    while (1)
    {
        skip_spaces(s, i);
        if (s[*i] == ']')
            break;
        parse_one_object(g, s, i);
        skip_spaces(s, i);
        if (s[*i] == ',')
            (*i)++;
    }

    expect(s, i, ']');
}

static void parse_one_object(t_game *g, char *s, int *i)
{
    char       *type_str = NULL;
    double      x = 0;
    double      y = 0;
    double      direction = 0;
    char       *sprite = NULL;
    t_objtype   type = OBJ_GENERIC;

    expect(s, i, '{');

    while (1)
    {
        char *k = parse_string(s, i);
        expect(s, i, ':');

        if (!strcmp(k, "type"))
        {
            type_str = parse_string(s, i);
            type = parse_obj_type(type_str);
        }
        else if (!strcmp(k, "x"))
            x = parse_number(s, i);
        else if (!strcmp(k, "y"))
            y = parse_number(s, i);
        else if (!strcmp(k, "direction"))
            direction = parse_number(s, i);   // ← player の時だけ使う
        else if (!strcmp(k, "sprite"))
            sprite = parse_string(s, i);
        else
        {
            /* 未知キー → 値スキップ（最低限の安全性） */
            parse_string(s, i);
        }

        free(k);

        skip_spaces(s, i);
        if (s[*i] == '}')
            break;
        expect(s, i, ',');
    }

    expect(s, i, '}');

    /*======== オブジェクト生成処理 =========*/

    t_object *obj = NULL;

    if (type == OBJ_PLAYER)
    {
        t_player *p = new_player(x, y, direction);  // ← player の direction をセット
        if (sprite)
            p->base.base.sprite_path = sprite;
        obj = (t_object *)p;
    }
    else if (type == OBJ_DOOR)
    {
        t_door *d = new_door(x, y);
        if (sprite)
            d->base.sprite_path = sprite;
        obj = (t_object *)d;
    }
    else if (type == OBJ_STRUCTURE)
    {
        t_structure *st = new_structure(x, y, 0);
        if (sprite)
            st->base.sprite_path = sprite;
        obj = (t_object *)st;
    }
    else if (type == OBJ_WALL)
    {
        obj = new_object(x, y, OBJ_WALL, sprite);
    }
    else
    {
        obj = new_object(x, y, type, sprite);
    }

    g->objects[g->obj_count++] = obj;

    if (type_str)
        free(type_str);
}

/*
** ============================
** read file
** ============================
*/

static char *read_all(char *path)
{
    int     fd;
    char    buf[4096];
    int     n;
    int     cap = 4096;
    int     len = 0;
    char    *s;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);

    s = malloc(cap);
    if (!s)
        return (NULL);

    while ((n = read(fd, buf, 4096)) > 0)
    {
        if (len + n + 1 >= cap)
        {
            cap = (cap + n) * 2;
            char *new = malloc(cap);
            memcpy(new, s, len);
            free(s);
            s = new;
        }
        memcpy(s + len, buf, n);
        len += n;
    }
    close(fd);
    s[len] = '\0';
    return s;
}

static char *read_all_fd(int fd)
{
    char buf[4096];
    int  n;
    int  cap = 4096;
    int  len = 0;
    char *s = malloc(cap);

    if (!s)
        return NULL;

    while ((n = read(fd, buf, 4096)) > 0)
    {
        if (len + n + 1 >= cap)
        {
            cap = (cap + n) * 2;
            char *new = malloc(cap);
            if (!new) { free(s); return NULL; }
            memcpy(new, s, len);
            free(s);
            s = new;
        }
        memcpy(s + len, buf, n);
        len += n;
    }
    s[len] = '\0';
    return s;
}

/*
** ============================
** parse_game_json (Main Entry)
** ============================
*/

void parse_game_json_str(t_game *g, char *s)
{
    int i = 0;

    skip_spaces(s, &i);
    expect(s, &i, '{');

    while (1)
    {
        char *key = parse_string(s, &i);
        expect(s, &i, ':');

        if (!strcmp(key, "map"))
            parse_map(g, s, &i);
        else if (!strcmp(key, "textures"))
            parse_textures(g, s, &i);
        else if (!strcmp(key, "colors"))
            parse_colors(g, s, &i);
        else if (!strcmp(key, "objects"))
            parse_objects(g, s, &i);
        else if (!strcmp(key, "width"))
            g->map.width = (int)parse_number(s, &i);
        else if (!strcmp(key, "height"))
            g->map.height = (int)parse_number(s, &i);

        free(key);

        skip_spaces(s, &i);
        if (s[i] == '}')
            break;
        expect(s, &i, ',');
    }

    expect(s, &i, '}');
}


void print_game(t_game *g)
{
    int i;

    printf("==== MAP ====\n");
    i = 0;
    while (g->map.grid[i])
    {
        printf("%s\n", g->map.grid[i]);
        i++;
    }

    printf("\n==== COLORS ====\n");
    printf("floor:   %d,%d,%d\n",
        g->colors.floor.r, g->colors.floor.g, g->colors.floor.b);
    printf("ceiling: %d,%d,%d\n",
        g->colors.ceiling.r, g->colors.ceiling.g, g->colors.ceiling.b);

    printf("\n==== TEXTURES ====\n");
    printf("NO: %s\n", g->tex.no);
    printf("SO: %s\n", g->tex.so);
    printf("WE: %s\n", g->tex.we);
    printf("EA: %s\n", g->tex.ea);

    printf("\n==== OBJECTS (%d個) ====\n", g->obj_count);
    i = 0;
    while (i < g->obj_count)
    {
        t_object *o = g->objects[i];

        // 共通表示
        printf("[%d] type=%d x=%.2f y=%.2f sprite=%s",
            i, o->type, o->x, o->y,
            o->sprite_path ? o->sprite_path : "(none)");

        // Player のときだけ direction 表示
        if (o->type == OBJ_PLAYER)
        {
            t_player *p = (t_player *)o;  // ← 派生型にキャスト
            printf(" direction=%.2f", p->direction);
        }

        printf("\n");
        i++;
    }
}

// ウィンドウの×を押した時
int close_window(void *param)
{
	(void)param;
	printf("window closed.\n");
	exit(0);
	return (0);
}

int walkable(t_game *g, double x, double y)
{
    int i;
    t_object *o;

    for (i = 0; i < g->obj_count; i++)
    {
        o = g->objects[i];
        if (o->type == OBJ_WALL)
        {
            if ((int)o->x == (int)x && (int)o->y == (int)y)
                return (0);
        }
    }
    return (1);
}
t_player *get_player(t_game *g)
{
    int i;
    for (i = 0; i < g->obj_count; i++)
        if (g->objects[i]->type == OBJ_PLAYER)
            return ((t_player *)g->objects[i]);
    return (NULL);
}

int key_press(int key, t_game *g)
{
    t_player *p = get_player(g);
    double nx, ny;

    if (!p)
        return (0);

    if (key == 53) // ESC
        exit_game(g);

    nx = p->base.base.x;
    ny = p->base.base.y;

    if (key == 13) // W
        ny -= 1;
    else if (key == 1) // S
        ny += 1;
    else if (key == 0) // A
        nx -= 1;
    else if (key == 2) // D
        nx += 1;

    // 衝突判定
    if (walkable(g, nx, ny))
    {
        p->base.base.x = nx;
        p->base.base.y = ny;
    }

    // 再描画
    mlx_clear_window(g->sys.mlx, g->sys.win);
    draw_world(g);

    return (0);
}

int exit_game(t_game *g)
{
    texmgr_destroy(&g->texmgr, g->sys.mlx);

    mlx_destroy_window(g->sys.mlx, g->sys.win);
    exit(0);
    return (0);
}

void init_map(t_map *m)
{
    m->grid = NULL;
    m->height = 0;
    m->width = 0;
}

int main(int argc, char **argv)
{
    t_game g;
    char *json;

    // if (argc != 2)
    //     return (printf("Usage: ./cub3D map.json\n"), 1);

    (void)argc;
    
    // 0. 初期化
    memset(&g, 0, sizeof(t_game));
    init_map(&g.map);     // 必要なら so_long の癖として用意
    g.obj_count = 0;

    // 1. MLX 初期化
    g.sys.mlx = mlx_init();
    if (!g.sys.mlx)
    {
        printf("mlx_init failed\n");
        return (1);
    }
    g.sys.win = mlx_new_window(g.sys.mlx, 800, 600, "cub3D (JSON)");
    if (!g.sys.win)
    {
        printf("mlx_new_window failed\n");
        return (1);
    }

    // 2. texture manager 初期化（空読みなど）
    texmgr_init(&g.texmgr, g.sys.mlx);

    // 3. JSON パース
    if (argc == 2)
    {
        // ファイルから読む
        json = read_all(argv[1]);
    }
    else
    {
        // パイプなど標準入力から読む
        json = read_all_fd(0);
    }

    if (!json)
    {
        write(2, "JSON read error\n", 16);
        return 1;
    }

    parse_game_json_str(&g, json);

    // 4. プレイヤーの追加初期化（direction → ベクトル）
    // t_player *player = find_player(&g);
    // init_player_camera(player);

    // 5. 初回描画
    draw_world(&g);

    // 6. イベントフック
    mlx_hook(g.sys.win, 2, 1L<<0, key_press, &g);  // key press
    mlx_hook(g.sys.win, 17, 0, exit_game, &g);      // close

    // 7. メインループ
    mlx_loop(g.sys.mlx);

    free(json);

    return (0);
}

// int main(int argc, char **argv)
// {
//     t_game g;
//     char *json;

//     memset(&g, 0, sizeof(t_game));

//     if (argc == 2)
//     {
//         // ファイルから読む
//         json = read_all(argv[1]);
//     }
//     else
//     {
//         // パイプなど標準入力から読む
//         json = read_all_fd(0);
//     }

//     if (!json)
//     {
//         write(2, "JSON read error\n", 16);
//         return 1;
//     }

//     parse_game_json_str(&g, json);
//     print_game(&g);

//     free(json);
//     return 0;
// }
