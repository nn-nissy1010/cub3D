/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:56:26 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/25 21:32:04 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MAX_BUFFER_SIZE
#  define MAX_BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*buf_add_line(int fd, char *save);
char	*gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_strjoin(const char *str1, const char *str2);
char	*gnl_ft_substr(const char *s, unsigned int start, size_t len);
char	*gnl_ft_strdup(const char *str);
size_t	gnl_ft_strlen(const char *str);

#endif
