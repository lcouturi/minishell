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

static void	exec_proc_loop(int i, char **paths, char **args, char **envp)
{
	int		n;
	char	*path;

	n = ft_strlen(paths[i]) + ft_strlen(args[0]) + 2;
	path = malloc(n);
	if (!path)
	{
		strarrfree(envp);
		strarrfree(paths);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(path, paths[i], n);
	ft_strlcat(path, "/", n);
	ft_strlcat(path, args[0], n);
	if (!access(path, X_OK))
	{
		strarrfree(paths);
		execve(path, args, envp);
	}
	free(path);
}

static void	exec_proc(char **args, char **envp)
{
	int		i;
	char	**paths;

	if (!access(args[0], X_OK))
		execve(args[0], args, envp);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (paths[++i])
		exec_proc_loop(i, paths, args, envp);
	printf("minishell: %s: command not found\n", args[0]);
	strarrfree(envp);
	strarrfree(paths);
	strarrfree(args);
	exit(EXIT_FAILURE);
}

void	exec_child(char **args, char **envp, int fds[])
{
	int	pipe_check;

	(void)pipe_check;
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	(void)fds;
	exec_proc(args, envp);
	exit(g_exit_status);
}

void	exec_parents(int pid, int fds[])
{
	close(fds[1]);
	close(fds[0]);
	printf("hi\n");
	waitpid(pid, &g_exit_status, 0);
	g_exit_status = g_exit_status >> 8;
}

void	cmd_exec(char **args, char **envp, int pipe_check)
{
	int	pid;
	int	fds[2];

	pid = fork();
	pipe(fds);
	if (pipe_check == 0)
	{
		if (!pid)
			exec_proc(args, envp);
		waitpid(pid, &g_exit_status, 0);
	}
	else
	{
		if (!pid)
			exec_proc(args, envp);
		else
			exit(EXIT_FAILURE);
		if (pid == 0)
			exec_child(args, envp, fds);
		else
			exec_parents(pid, fds);
	}
}
