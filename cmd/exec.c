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

static void	get_path_loop(int i, char **paths, char **args, char **envp)
{
	char	*single_path;
	char	*single_path2;

	single_path2 = ft_strjoin(paths[i], "/");
	if (!single_path2)
	{
		free_string_array(paths);
		exit(EXIT_FAILURE);
	}
	single_path = ft_strjoin(single_path2, args[0]);
	free(single_path2);
	if (!single_path)
	{
		free_string_array(paths);
		exit(EXIT_FAILURE);
	}
	if (!access(single_path, X_OK))
	{
		free_string_array(paths);
		execve(single_path, args, envp);
	}
	free(single_path);
}

static int	get_path(char **args, char **envp)
{
	int		i;
	char	**paths;
	char	*single_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	single_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!single_path)
		exit(EXIT_FAILURE);
	paths = ft_split(single_path, ':');
	free(single_path);
	if (!paths)
		exit(EXIT_FAILURE);
	i = -1;
	while (paths[++i])
		get_path_loop(i, paths, args, envp);
	free_string_array(paths);
	return (0);
}

void	cmd_exec(char **args, char **envp)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		else if (!get_path(args, envp))
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, 0, 0);
}
