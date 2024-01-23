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

static void	cmd_exec_loop(int i, char **paths, char **args, char **envp)
{
	int		n;
	char	*path;

	n = ft_strlen(paths[i]) + ft_strlen(args[0]) + 2;
	path = malloc(n);
	if (!path)
	{
		free_string_array(envp);
		free_string_array(paths);
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(path, paths[i], n);
	ft_strlcat(path, "/", n);
	ft_strlcat(path, args[0], n);
	if (!access(path, X_OK))
	{
		free_string_array(paths);
		execve(path, args, envp);
	}
	free(path);
}

void	cmd_exec(char **args, char **envp)
{
	int		i;
	int		pid;
	char	**paths;

	pid = fork();
	if (!pid)
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		i = 0;
		while (ft_strncmp(envp[i], "PATH=", 5))
			i++;
		paths = ft_split(envp[i] + 5, ':');
		if (!paths)
		{
			free_string_array(envp);
			exit(EXIT_FAILURE);
		}
		i = -1;
		while (paths[++i])
			cmd_exec_loop(i, paths, args, envp);
		printf("minishell: %s: command not found\n", args[0]);
		free_string_array(envp);
		free_string_array(paths);
		free_string_array(args);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &g_exit_status, 0);
}
