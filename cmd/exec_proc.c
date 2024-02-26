/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/16 22:21:53 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_edgecase(t_node *node, char **args, char **envp, char **paths)
{
	char	*test;
	char	*test2;

	test = ft_strjoin(node->pwd, "/");
	test2 = ft_strjoin(test, args[0]);
	free(test);
	if (!access(test2, X_OK))
	{
		free(test2);
		execve(args[0], args, envp);
	}
	free(test2);
	exec_error(args, envp, paths);
}

static void	exec_proc_loop2(char **paths, char **args, char **envp,
		t_node *node)
{
	char	**temp;

	if (node->redir_flag && ft_strncmp(args[0], "<<", 3))
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
	chkdir(&node->path, envp, 0);
	free(node->path);
}

static void	exec_proc_loop(char **paths, char **args, char **envp, t_node *node)
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

void	exec_proc(char **args, char **envp, t_node *node)
{
	char	**paths;

	if (!args[0][0])
		exec_error(args, envp, 0);
	checkdot(args, envp);
	if (ft_strchr(args[0], '/'))
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		chkdir(args, envp, 1);
	}
	paths = ft_split(ft_getenv("PATH", envp), ':');
	if (!paths)
		exec_edgecase(node, args, envp, paths);
	node->i = -1;
	while (paths[++(node->i)])
		exec_proc_loop(paths, args, envp, node);
	exec_error(args, envp, paths);
}
