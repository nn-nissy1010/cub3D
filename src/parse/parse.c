/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:33:10 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/27 21:35:01 by tkuwahat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/parse.c
#include "main.h"

static int  handle_line(t_game *g, char *line);
static int  handle_tex_or_color(t_game *g, char **sp);
static int  add_map_line(t_game *g, char *line);

int parse_cub(t_game *g, const char *path)
{
    int     fd;
    char    *line;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("cannot open cub file");
        return (1);
    }
    while ((line = get_next_line(fd)))
    {
        if (handle_line(g, line))
        {
            free(line);
            close(fd);
            return (1);
        }
        free(line);
    }
    close(fd);

    if (build_map_grid(&g->map))
    {
        printf("DEBUG: build_map_grid failed\n");
        return (1);
    }
    if (validate_map(&g->map))
    {
        printf("DEBUG: validate_map failed\n");
        return (1);
    }
    if (spawn_objects_from_map(g))
    {
        printf("DEBUG: spawn_objects_from_map failed\n");
        return (1);
    }
    return (0);
}

void chop_newline(char *s)
{
    int len = ft_strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

static int handle_line(t_game *g, char *line)
{
    char **sp;

    chop_newline(line);
    if (is_empty(line))
        return (0);

    sp = ft_split(line, ' ');
    if (!sp)
        return (1);

    if (is_tex_id(sp[0]) || is_color_id(sp[0]))
    {
        if (handle_tex_or_color(g, sp))
            return (free_split(sp), 1);
        return (free_split(sp), 0);
    }
    free_split(sp);
    return (add_map_line(g, line));
}

static int handle_tex_or_color(t_game *g, char **sp)
{
    if (is_tex_id(sp[0]))
        return set_texture(&g->tex, sp[0], sp[1]);
    if (is_color_id(sp[0]))
        return set_color(&g->colors, sp[0], sp[1]);
    return (1);
}

static int add_map_line(t_game *g, char *line)
{
    return push_map_line(&g->map, line);
}