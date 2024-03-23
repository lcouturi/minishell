/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
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

void	chkdir(char **args, char **envp, bool end)
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
		perror(args[0]);
		if (end && errno != EISDIR)
			status = 127;
		else
			status = 126;
	}
	strarrfree(envp);
	strarrfree(args);
	exit(status);
}

void	exec_error(char **args, char **envp, char **paths, t_node *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ft_strchr(args[0], '/') || !paths)
	{
		errno = ENOENT;
		perror(args[0]);
	}
	else
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	strarrfree(envp);
	if (paths)
		strarrfree(paths);
	if (node->pipe_flag)
		strarrfree(args);
	else
		strarrfree(args - node->pipe_idx);
	exit(127);
}

void	checkdot(char **args, char **envp)
{
	if (!ft_strncmp(args[0], ".", 2))
	{
		ft_putstr_fd("minishell: .: filename argument required", STDERR_FILENO);
		ft_putstr_fd("\n.: usage: . filename [arguments]\n", STDERR_FILENO);
		strarrfree(envp);
		strarrfree(args);
		exit(127);
	}
	if (!ft_strncmp(args[0], "..", 3))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}
