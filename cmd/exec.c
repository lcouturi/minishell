/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:21:53 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_proc_loop2(char **paths, char **args,
					char **envp, t_node *node)
{
	char	**temp;

	if (node->redir_flag)
		argu_left_change(args);
	if (!access(node->path, X_OK))
	{
		strarrfree(paths);
		if (node->pipe_flag)
		{
			temp = split_before_pipe_args(args, node);
			execve(node->path, temp, envp);
			free(temp);
		}
		else
			execve(node->path, args, envp);
	}
	free(node->path);
}

static void	exec_proc_loop(char **paths, char **args,
					char **envp, t_node *node)
{
	int	n;

	n = ft_strlen(paths[node->i]) + ft_strlen(args[0]) + 2;
	node->path = malloc(n);
	if (!(node->path))
	{
		strarrfree(envp);
		strarrfree(paths);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(node->path, paths[node->i], n);
	ft_strlcat(node->path, "/", n);
	ft_strlcat(node->path, args[0], n);
	exec_proc_loop2(paths, args, envp, node);
}

static void	strarrfree_all(char **args, char **envp, char	**paths)
{
	strarrfree(envp);
	strarrfree(paths);
	strarrfree(args);
}

static void	exec_proc(char **args, char **envp, t_node *node)
{
	char	**paths;

	if (!access(args[0], X_OK))
		execve(args[0], args, envp);
	node->i = 0;
	while (ft_strncmp(envp[node->i], "PATH=", 5))
		node->i += 1;
	paths = ft_split(envp[node->i] + 5, ':');
	if (!paths)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	node->i = -1;
	while (paths[++(node->i)])
		exec_proc_loop(paths, args, envp, node);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	strarrfree_all(args, envp, paths);
	exit(127);
}

void	cmd_exec(char **args, char **envp, t_node *node)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
		exec_proc(args, envp, node);
	waitpid(pid, &status, 0);
	g_exit_status = status / 256;
}
