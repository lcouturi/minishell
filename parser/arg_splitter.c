/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/17 18:12:51 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	sep(char s, char c)
{
	if (!s || s == c)
		return (1);
	return (0);
}

static char	**loop(char const *s, char c, char **returned, int *i)
{
	while (i[0]--)
	{
		if (i[0] && sep(s[i[0]], c) == 1 && sep(s[i[0] - 1], c) == 0)
		{
			i[1] = i[0]--;
			while (i[0] && !(sep(s[i[0]], c) == 1 && sep(s[i[0] - 1], c) == 0))
				i[0]--;
			while (sep(s[i[0]], c) == 1)
				i[0]++;
			i[2]--;
			returned[i[2]] = ft_substr(s, i[0], i[1] - i[0]);
			if (!returned[i[2]])
			{
				while (returned[++i[2]])
					free(returned[i[2]]);
				free(returned);
				return (0);
			}
			i[0] = i[1];
		}
	}
	return (returned);
}

static char	*whitespace_hack(char *s)
{
	int	i;

	i = -1;
	while (++i)
		if (s[i] == 9 || s[i] == 10 || s[i] == 11 || s[i] == 12 || s[i] == 13)
			s[i] = ' ';
	return (s);
}

static int	wordcount(char const *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s && s[i])
	{
		if ((sep(s[i], c) == 0) && sep(s[i + 1], c) == 1)
			wc++;
		i++;
	}
	return (wc);
}

char	**arg_splitter(char *s)
{
	int		i[3];
	char	**returned;

	s = whitespace_hack(s);
	i[1] = 0;
	i[2] = wordcount(s, ' ');
	returned = malloc((i[2] + 1) * 8);
	if (!s || !returned)
		return (0);
	i[0] = ft_strlen(s) + 1;
	returned[i[2]] = 0;
	return (loop(s, ' ', returned, i));
}
