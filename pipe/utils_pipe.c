/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/27 09:21:21 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(char **args, char **envp, t_node *node)
{
	node->exit_flag = 0;
	close(node->fds[0]);
	dup2(node->fds[1], STDOUT_FILENO);
	close(node->fds[1]);
	if (node->child_die == 0)
		envp = find_command(args, envp, node);
	exit(g_exit_status);
}

void	exec_parents(int pid, char **args, char **envp, t_node *node)
{
	int	status;

	node->exit_flag = 0;
	waitpid(pid, &status, 0);
	g_exit_status = status >> 8;
	close(node->fds[1]);
	dup2(node->fds[0], STDIN_FILENO);
	close(node->fds[0]);
	node->pipe_flag = 0;
	if (repeat_check(args + node->pipe_idx, node))
		envp = repeat(args + node->pipe_idx, envp, node);
	else
	{
		node->redir_flag = redir_chk(node->ori_args + node->pipe_idx);
		redir_excute(args + node->pipe_idx, envp, node);
		envp = find_command(args + node->pipe_idx, envp, node);
	}
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
	strarrfree(envp);
}

char	**cloturn(int backup_stdout, int backup_stdin, char **envp)
{
	close(backup_stdout);
	close(backup_stdin);
	return (envp);
}

int	pipe_check(char **args, t_node *node)
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
			{
				node->pipe_idx = i + 1;
				node->pipe_flag = 1;
				return (1);
			}
		}
		i++;
	}
	node->pipe_flag = 0;
	return (0);
}

void	init_node(t_node *node)
{
	node->pipe_idx = 0;
	node->quota_pipe_cnt = 0;
	node->echo_skip = 0;
	node->child_die = 0;
	node->exit_flag = 1;
}
