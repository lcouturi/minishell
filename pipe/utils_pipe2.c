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

void	backup_restor(t_node *node)
{
	dup2(node->backup_stdout, STDOUT_FILENO);
	dup2(node->backup_stdin, STDIN_FILENO);
}

char	**split_before_pipe_args(char **args, t_node *node)
{
	char	**temp;
	int		i;
	int		j;

	i = -1;
	temp = malloc((node->pipe_idx + 1) * sizeof(char *));
	if (!temp)
		exit(EXIT_FAILURE);
	while (++i < node->pipe_idx - 1)
	{
		temp[i] = malloc(ft_strlen(args[i]));
		if (!temp[i])
			exit(EXIT_FAILURE);
		j = 0;
		while (args[i][j])
		{
			temp[i][j] = args[i][j];
			j++;
		}
		temp[i][j] = '\0';
	}
	temp[i] = NULL;
	return (temp);
}

void	backup(t_node *node)
{
	node->backup_stdout = dup(STDOUT_FILENO);
	node->backup_stdin = dup(STDIN_FILENO);
}

char	**repeat(char **args, char **envp, t_node *node)
{
	int	pid;

	pid = 0;
	if (redir_excute(args, node))
		return (envp);
	if (pipe_check(args, node))
	{
		pipe(node->fds);
		pid = fork();
		if (pid < 0)
			return (envp);
	}
	else
	{
		envp = find_command(args, envp, node);
		if (node->redir_flag != 0)
			backup_restor(node);
		return (envp);
	}
	if (pid == 0)
		exec_child(args, envp, node);
	else
		exec_parents(pid, args, envp, node);
	return (envp);
}

char	**execute(char **args, char **envp, t_node *node)
{
	backup(node);
	envp = repeat(args, envp, node);
	backup_restor(node);
	return (cloturn(node->backup_stdout, node->backup_stdin, envp));
}
