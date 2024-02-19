/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/24 00:40:30 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	new_len(char **args)
{
	char	c;
	int		i;
	int		j;
	int		l;

	i = -1;
	l = 0;
	while (args[++i])
	{
		if (isop(args[i][0]))
		{
			j = 0;
			while (args[i][j])
			{
				c = args[i][j];
				while (args[i][j] && args[i][j] == c)
					j++;
				l++;
			}
		}
		else
			l++;
	}
	return (l);
}

static void	split_operators_loop(char **args, char **args_new, int i, int *l)
{
	char		c;
	int			j;
	int			k;
	int			m;

	if (isop(args[i][0]))
	{
		j = 0;
		k = 0;
		while (args[i][j])
		{
			c = args[i][j];
			while (args[i][j] && args[i][j] == c)
				j++;
			args_new[*l] = malloc((j + 1) * sizeof(char));
			m = 0;
			while (args[i][k] && args[i][k] == c)
				args_new[*l][m++] = args[i][k++];
			args_new[(*l)++][m] = '\0';
		}
	}
	else
		args_new[(*l)++] = ft_strdup(args[i]);
}

char	**split_operators(char **args)
{
	char	**args_new;
	int		i;
	int		l;

	i = -1;
	l = 0;
	args_new = malloc((new_len(args) + 1) * 8);
	while (args[++i])
		split_operators_loop(args, args_new, i, &l);
	args_new[l] = 0;
	strarrfree(args);
	return (args_new);
}
