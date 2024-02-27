/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:48:00 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	left_redir(char **args, int i, t_node *node)
{
	int	fd;

	if (access(args[i + 1], R_OK))
		return (print_err(args, i, node));
	fd = open(args[i + 1], O_RDONLY, 0744);
	if (fd <= 0)
		return (1);
	if (!ft_strncmp(args[0], "echo", 5))
	{
		args_left_move(args, i);
		if (ft_strncmp(args[i + 1], "<", 2) && ft_strncmp(args[i + 1], "|", 2))
			args_left_move(args, i);
	}
	else
		args[i] = NULL;
	if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "./", 2)
		&& !args[2])
		node->echo_skip = 1;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	left_double_redir(char **args, char **envp, int i)
{
	char	*line;
	int		fd;

	fd = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!args[i + 1] || !ft_strncmp(args[i + 1], " ", ft_strlen(args[i + 1])))
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", STDERR_FILENO);
		ft_putstr_fd("token `newline'\n", STDERR_FILENO);
		return (1);
	}
	line = get_line("> ");
	while (ft_strncmp((line), args[i + 1], ft_strlen(args[i + 1]) + 1))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = get_line("> ");
		line = expand_envvar(line, envp);
	}
	lseek(fd, 0, SEEK_SET);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (unlink(".temp"))
		return (1);
	return (0);
}

static void	args_cha(char **args, int i)
{
	if (!ft_strncmp(args[0], "echo", 5))
	{
		args_left_move(args, i);
		if (!is_redir(args, i, 0) && ft_strncmp(args[i], "|", 2))
			args_left_move(args, i);
	}
	else
		args[i] = NULL;
}

int	right_redir(char **args, char **envp, int i, t_node *node)
{
	int	fd;

	if (exec_check(args, envp) || node->redir_idx)
	{
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd <= 0)
		{
			if (!node->pipe_idx)
				return (print_err(args, i, node));
			exit(EXIT_FAILURE);
		}
		node->right_flag = 1;
		args_cha(args, i);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	right_double_redir(char **args, char **envp, int i, t_node *node)
{
	int	fd;

	args[i] = NULL;
	if (exec_check(args, envp))
	{
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
		if (fd <= 0)
		{
			if (!node->pipe_idx)
				return (print_err(args, i, node));
			exit(EXIT_FAILURE);
		}
		node->right_flag = 1;
		args_cha(args, i);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
