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

void	redir_excute(char **args, char **envp, t_node *node)
{
	if (node->redir_flag)
	{
		if (exec_redir(args, envp, node))
			return ;
	}
}

int	repeat_check(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
		{
			if (node->quota_idx_j < node->quota_pipe_cnt
				&& node->quota_pipe_idx_arr[node->quota_idx_j] == i)
				(node->quota_idx_j)++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}
