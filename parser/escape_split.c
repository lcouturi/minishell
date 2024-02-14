/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/29 19:12:11 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	sep(char s, int *i, char c)
{
	if (!s || (!i[3] && !i[4] && s == c))
		return (1);
	return (0);
}

static void	loop(char *s, char **returned, int *i, char c)
{
	quote_check(s, i);
	if (i[0] && sep(s[i[0]], i, c) && !sep(s[i[0] - 1], i, c))
	{
		i[1] = i[0]--;
		while (i[0] && !(sep(s[i[0]], i, c) && !sep(s[i[0] - 1], i, c)))
		{
			i[0]--;
			quote_check(s, i);
		}
		while (sep(s[i[0]], i, c))
		{
			i[0]++;
			quote_check(s, i);
		}
		i[2]--;
		returned[i[2]] = ft_substr(s, i[0], i[1] - i[0]);
		if (!returned[i[2]])
		{
			while (returned[++i[2]])
				free(returned[i[2]]);
			free(returned);
			exit(EXIT_FAILURE);
		}
		i[0] = i[1];
	}
}

char	**escape_split(char *s, char c)
{
	int		i[5];
	char	**returned;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	while (s[++i[0]])
	{
		quote_check(s, i);
		if (!sep(s[i[0]], i, c) && sep(s[i[0] + 1], i, c))
			i[2]++;
	}
	i[0] = ft_strlen(s) + 1;
	returned = malloc((i[2] + 1) * 8);
	if (!returned)
	{
		free(s);
		exit(EXIT_FAILURE);
	}
	returned[i[2]] = 0;
	while (i[0]--)
		loop(s, returned, i, c);
	return (returned);
}
