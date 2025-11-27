/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:56:42 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/25 21:27:50 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *before_newline(const char *s)
{
    size_t i = 0;

    if (!s || *s == '\0')
        return (NULL);
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    return (gnl_ft_substr(s, 0, i));
}

static char *after_newline(const char *s)
{
    char *p;

    if (!s)
        return (NULL);
    p = gnl_ft_strchr(s, '\n');
    if (!p || !*(p + 1))
        return (NULL);
    return (gnl_ft_strdup(p + 1));
}

static char *read_and_append(int fd, char *save)
{
    char    *buf;
    char    *tmp;
    ssize_t n;

    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);

    while (!gnl_ft_strchr(save, '\n'))
    {
        n = read(fd, buf, BUFFER_SIZE);
        if (n <= 0)
            break;
        buf[n] = '\0';
        if (!save)
            save = gnl_ft_strdup("");
        tmp = gnl_ft_strjoin(save, buf);
        free(save);
        save = tmp;
    }
    free(buf);
    return (save);
}

char *get_next_line(int fd)
{
    static char *save;
    char        *full;
    char        *line;
    char        *next;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    full = read_and_append(fd, save);
    if (!full || *full == '\0')
    {
        free(full);
        save = NULL;
        return (NULL);
    }

    line = before_newline(full);
    next = after_newline(full);

    free(full);
    save = next;

    return (line);
}
