/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir3.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:07 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	two_left_redir(char **args)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (args && args[++i] && ft_strncmp(args[i], "|", 2))
		if (!ft_strncmp(args[i], "<", 2))
			num += 10;
	return (num == 20);
}

int	two_redir(char **args, t_node *node)
{
	int	i;
	int	num;

	i = -1;
	num = -1;
	if (two_left_redir(args))
		return (0);
	while (args && args[++i] && ft_strncmp(args[i], "|", 2))
		if (is_redir_check(args[i]))
			if (++num == 1)
				node->redir_idx = i;
	return (num >= 2);
}

void	exec_redir_child(char **args, char **envp, t_node *node, int *flag)
{
	node->redir_stop = 0;
	if (node->redir_flag)
	{
		if (node->redir_idx)
		{
			close(node->redir_fds[0]);
			dup2(node->redir_fds[1], STDOUT_FILENO);
			close(node->redir_fds[1]);
			if (exec_redir(args, envp, node))
				*flag = 1;
			return ;
		}
		else if (exec_redir(args, envp, node))
			*flag = 1;
	}
}

void	exec_redir_parents(char **args, char **envp, t_node *node, int *flag)
{
	int	status;

	waitpid(-1, &status, 0);
	close(node->redir_fds[1]);
	dup2(node->redir_fds[0], STDIN_FILENO);
	close(node->redir_fds[0]);
	if (exec_redir(args, envp, node))
		*flag = 1;
	args_left_move_i(args, node);
}

bool	is_redir_check(char *str)
{
	return (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3) || !ft_strncmp(str, "<<", 3));
}
