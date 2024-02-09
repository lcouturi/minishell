/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:07 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_chk(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp("<<", args[i], 3) || !ft_strncmp(">>", args[i], 3)
			|| !ft_strncmp("<", args[i], 2) || !ft_strncmp(">", args[i], 2))
			return (1);
	}
	return (0);
}

void	argu_long(char **args, int k, int len)
{
	free(args[k]);
	free(args[k + 1]);
	args[k + 1] = NULL;
	while (k + 2 < len)
	{
		args[k] = ft_strdup(args[k + 2]);
		free(args[k + 2]);
		args[k + 2] = NULL;
		k++;
	}
}

void	argu_two(char **args, int k)
{
	free(args[k]);
	free(args[k + 1]);
	args[k] = NULL;
	args[k + 1] = NULL;
}

void	argu_left_change(char **args)
{
	int	i;
	int	k;
	int	len;

	i = -1;
	len = strarrlen(args);
	while (args[++i])
	{
		if (ft_strncmp(args[i], "<<", 3) == 0)
		{
			k = i;
			if (k + 1 == len)
			{
				free(args[k]);
				args[k] = NULL;
			}
			else if (k + 2 == len)
				argu_two(args, k);
			else
				argu_long(args, k, len);
		}
	}
}

int	redir_excute(char **args, t_node *node)
{
	if (node->redir_flag)
	{
		if (exec_redir(args))
			return (1);
	}
	return (0);
}
