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

char	**split_before_pipe_args(char **args, t_node *node)
{
	char	**temp;
	int		i;
	int		j;

	i = -1;
	temp = malloc((node->pipe_idx) * sizeof(char *));
	if (temp < 0)
		return (NULL);
	while (++i < node->pipe_idx - 1)
	{
		temp[i] = malloc(ft_strlen(args[i]));
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

static void	exec_proc_loop(char **paths, char **args,
					char **envp, t_node *node)
{
	int		n;
	char	*path;

	n = ft_strlen(paths[node->i]) + ft_strlen(args[0]) + 2;
	path = malloc(n);
	if (!path)
	{
		strarrfree(envp);
		strarrfree(paths);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(path, paths[node->i], n);
	ft_strlcat(path, "/", n);
	ft_strlcat(path, args[0], n);
	if (!access(path, X_OK))
	{
		strarrfree(paths);
		if (node->pipe_flag)
			execve(path, split_before_pipe_args(args, node), envp);
		else
			execve(path, args, envp);
	}
	free(path);
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
	printf("minishell: %s: command not found\n", args[0]);
	strarrfree(envp);
	strarrfree(paths);
	strarrfree(args);
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
	node->exit_status = status;
}
