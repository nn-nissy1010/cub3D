/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:50:44 by tkuwahat          #+#    #+#             */
/*   Updated: 2025/11/25 21:37:48 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *str)
{
	size_t	i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_ft_strdup(const char *str)
{
	size_t	i = 0;
	size_t	len;
	char	*dest;

	if (!str)
		return (NULL);
	len = gnl_ft_strlen(str);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*gnl_ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i = 0;
	size_t	s_len;
	size_t	sub_size;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = gnl_ft_strlen(s);
	if (start >= s_len)
		return (gnl_ft_strdup(""));   // ← 修正
	if (s_len - start > len)
		sub_size = len;
	else
		sub_size = s_len - start;

	substr = malloc(sub_size + 1);
	if (!substr)
		return (NULL);

	while (i < sub_size)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1, len2, i = 0, j = 0;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_ft_strdup(s2));
	if (!s2)
		return (gnl_ft_strdup(s1));

	len1 = gnl_ft_strlen(s1);
	len2 = gnl_ft_strlen(s2);

	dest = malloc(len1 + len2 + 1);
	if (!dest)
		return (NULL);

	while (i < len1)
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';

	return (dest);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)       // ← これだけでNULLの安全性が付く
		return (NULL);

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (*str == (char)c)
		return (str);
	return (NULL);
}
