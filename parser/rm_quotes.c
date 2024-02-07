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

static char	*rm_quotes_loop(char *str)
{
	int		i[5];
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

void	quote_pipe_check(char **args, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	node->quota_idx_j = 0;
	j = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j + 1] && args[i][j + 2])
		{
			if (args[i][j] == '\'' && args[i][j + 1] == '|'
				&& args[i][j + 2] == '\'')
				node->quota_pipe_idx_arr[node->quota_pipe_cnt++] = j + 1;
			else if (args[i][j] == '\"' && args[i][j + 1] == '|'
				&& args[i][j + 2] == '\"')
				node->quota_pipe_idx_arr[node->quota_pipe_cnt++] = j + 1;
			j++;
		}
		i++;
	}
}

char	**rm_quotes(char **args, t_node *node)
{
	int	i;

	i = -1;
	quote_pipe_check(args, node);
	while (args[++i])
		args[i] = rm_quotes_loop(args[i]);
	return (args);
}

char	**rm_quotes_wildcards(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		args[i] = rm_quotes_loop(args[i]);
	return (args);
}
