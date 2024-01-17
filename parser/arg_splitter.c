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

static int	sep(char s, int *i)
{
	if ((!i[4] && s == '\"') || (!i[3] && s == '\''))
		return (1);
	else if (!i[3] && !i[4] && (!s || (s >= 9 && s <= 13) || s == 32))
		return (1);
	return (0);
}

static void	quote_check(char const *s, int *i)
{
	if (!i[4] && s[i[0]] == '\"')
	{
		if (!i[3])
			i[3] = 1;
		else
			i[3] = 0;
	}
	if (!i[3] && s[i[0]] == '\'')
	{
		if (!i[4])
			i[4] = 1;
		else
			i[4] = 0;
	}
}

static char	**loop(char const *s, char **returned, int *i)
{
	while (i[0]--)
	{
		quote_check(s, i);
		if (i[0] && sep(s[i[0]], i) == 1 && sep(s[i[0] - 1], i) == 0)
		{
			i[1] = i[0]--;
			while (i[0] && !(sep(s[i[0]], i) == 1 && sep(s[i[0] - 1], i) == 0))
				i[0]--;
			while (sep(s[i[0]], i) == 1)
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

char	**arg_splitter(char *s)
{
	int		i[5];
	char	**returned;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	while (s && s[i[0]])
	{
		quote_check(s, i);
		if ((sep(s[i[0]], i) == 0) && sep(s[i[0] + 1], i) == 1)
			i[2]++;
		i[0]++;
	}
	i[0] = ft_strlen(s) + 1;
	i[3] = 0;
	i[4] = 0;
	returned = malloc((i[2] + 1) * 8);
	if (!s || !returned)
		return (0);
	returned[i[2]] = 0;
	return (loop(s, returned, i));
}
