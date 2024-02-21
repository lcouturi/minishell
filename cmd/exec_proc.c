/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:21:53 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	chkdir_check(DIR *check, int err, bool end)
{
	if (check)
	{
		closedir(check);
		errno = EISDIR;
	}
	else if (err == EACCES)
		errno = EACCES;
	else if (!end)
		return (1);
	return (0);
}

static void	chkdir(char **args, char **envp, bool end)
{
	DIR			*check;
	int			err;
	struct stat	stats;
	int			status;

	err = errno;
	check = opendir(args[0]);
	status = 0;
	stat(args[0], &stats);
	if (chkdir_check(check, err, end))
		return ;
	if (errno != EACCES || stats.st_size)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(0);
		if (end && errno != EISDIR)
			status = 127;
		else
			status = 126;
	}
	strarrfree(envp);
	strarrfree(args);
	exit(status);
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
	if (ft_strchr(args[0], '/'))
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		chkdir(args, envp, 1);
	}
	node->i = 0;
	while (ft_strncmp(envp[node->i], "PATH=", 5))
		node->i++;
	paths = ft_split(envp[node->i] + 5, ':');
	if (!paths)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	node->i = -1;
	while (paths[++(node->i)])
		exec_proc_loop(paths, args, envp, node);
	exec_error(args, envp, paths);
}
