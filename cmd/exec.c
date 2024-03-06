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

static bool	exec_check_loop(char **paths, char **args)
{
	int		i;
	int		n;
	char	*path;

	i = -1;
	while (paths[++i])
	{
		n = ft_strlen(paths[i]) + ft_strlen(args[0]) + 2;
		path = malloc(n);
		if (!path)
		{
			strarrfree(paths);
			exit(EXIT_FAILURE);
		}
		ft_strlcpy(path, paths[i], n);
		ft_strlcat(path, "/", n);
		ft_strlcat(path, args[0], n);
		if (!access(path, X_OK))
		{
			free(path);
			return (1);
		}
		free(path);
	}
	return (0);
}

bool	exec_check(char **args, char **envp)
{
	char	**paths;
	bool	ret;

	if (!access(args[0], X_OK) || !ft_strncmp(args[0], "cd", 3)
		|| !ft_strncmp(args[0], "echo", 5) || !ft_strncmp(args[0], "env", 4)
		|| !ft_strncmp(args[0], "exit", 5) || !ft_strncmp(args[0], "export", 7)
		|| !ft_strncmp(args[0], "pwd", 4) || !ft_strncmp(args[0], "unset", 6))
		return (1);
	paths = ft_split(ft_getenv("PATH", envp), ':');
	if (!paths)
		exit(EXIT_FAILURE);
	ret = exec_check_loop(paths, args);
	strarrfree(paths);
	return (ret);
}
