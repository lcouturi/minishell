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
	if (!s || (!i[3] && !i[4] && ft_isspace(s)))
		return (1);
	return (0);
}

static void	loop(char *s, char **returned, int *i)
{
	quote_check(s, i);
	if (i[0] && sep(s[i[0]], i) == 1 && sep(s[i[0] - 1], i) == 0)
	{
		i[1] = i[0]--;
		while (i[0] && !(sep(s[i[0]], i) == 1 && sep(s[i[0] - 1], i) == 0))
		{
			i[0]--;
			quote_check(s, i);
		}
		while (sep(s[i[0]], i) == 1)
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
			return ;
		}
		i[0] = i[1];
	}
}

static char	*rm_quotes(char *str, int *i)
{
	int		j;
	int		l;
	char	*newstr;

	i[0] = -1;
	j = 0;
	l = 0;
	while (str[++i[0]])
	{
		quote_check(str, i);
		if (!(!i[4] && str[i[0]] == '\"') && !(!i[3] && str[i[0]] == '\''))
			l++;
	}
	newstr = malloc((l + 1) * sizeof(char));
	i[0] = -1;
	while (str[++i[0]])
	{
		quote_check(str, i);
		if (!(!i[4] && str[i[0]] == '\"') && !(!i[3] && str[i[0]] == '\''))
			newstr[j++] = str[i[0]];
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	**arg_splitter(char *s)
{
	int		i[5];
	int		j;
	char	**returned;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	while (s && s[++i[0]])
	{
		quote_check(s, i);
		if ((sep(s[i[0]], i) == 0) && sep(s[i[0] + 1], i) == 1)
			i[2]++;
	}
	i[0] = ft_strlen(s) + 1;
	returned = malloc((i[2] + 1) * 8);
	if (!s || !returned)
		return (0);
	returned[i[2]] = 0;
	while (i[0]--)
		loop(s, returned, i);
	j = -1;
	while (returned[++j])
		returned[j] = rm_quotes(returned[j], i);
	j = -1;
	free(s);
	return (returned);
}
