/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/27 09:21:21 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_child(char **args, char **envp, t_node *node)
{
	close(node->fds[0]);
	dup2(node->fds[1], STDOUT_FILENO);
	close(node->fds[1]);
	envp = find_command(args, envp, node);
	exit(node->exit_status);
}

void	exec_parents(int pid, char **args, char **envp, t_node *node)
{
	int	status;

	waitpid(pid, &status, 0);
	node->exit_status = status >> 8;
	close(node->fds[1]);
	dup2(node->fds[0], STDIN_FILENO);
	close(node->fds[0]);
	node->pipe_flag = 0;
	envp = find_command(args + node->pipe_idx, envp, node);
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
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
			node->pipe_idx = i + 1;
			node->pipe_flag = 1;
			return (1);
		}
		i++;
	}
	node->pipe_flag = 0;
	return (0);
}

void	init_node(t_node *node)
{
	node->pipe_idx = 0;
}
