/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2023/11/23 18:06:27 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gn_strchr(const char *s, int c)
{
	while (s && *s && *s != c % 256)
		s++;
	if (s && *s == c % 256)
		return ((char *)s);
	return (0);
}

static size_t	gn_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static size_t	gn_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i[2];
	size_t	dest_size;

	i[0] = gn_strlen(dst);
	i[1] = 0;
	dest_size = i[0];
	if (dstsize < dest_size || !dst || !src)
		return (dstsize + gn_strlen(src));
	while (src[i[1]] && i[0] < dstsize)
	{
		dst[i[0]] = src[i[1]];
		i[0]++;
		i[1]++;
	}
	if (dest_size == dstsize)
		dst[dest_size] = '\0';
	else if (i[0] < dstsize)
		dst[i[0]++] = '\0';
	else if (i[0] >= dstsize)
		dst[dstsize - 1] = '\0';
	return (dest_size + gn_strlen(src));
}

char	*gn_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	while (s1 && s1[i])
		i++;
	s2 = malloc((i + 1) * sizeof(char));
	if (!s1 || !s2)
		return (s2);
	s2[0] = '\0';
	gn_strlcat(s2, s1, gn_strlen(s1) + 1);
	return (s2);
}

char	*gn_strjoin(char *s1, char const *s2)
{
	char	*r;

	r = malloc((gn_strlen(s1) + gn_strlen(s2) + 1) * sizeof(char));
	if (!r)
		return (r);
	r[0] = '\0';
	gn_strlcat(r, s1, gn_strlen(s1) + gn_strlen(s2) + 1);
	gn_strlcat(r, s2, gn_strlen(s1) + gn_strlen(s2) + 1);
	free(s1);
	return (r);
}
