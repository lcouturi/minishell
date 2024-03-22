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

int	left_redir(char **args, char **envp, int *i, t_node *node)
{
	int	fd;

	if (access(args[*i + 1], R_OK))
		return (print_err(args, *i, node));
	fd = open(args[*i + 1], O_RDONLY, 0744);
	if (fd <= 0)
		return (1);
	if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "./", 2)
		&& !args[2])
		node->echo_skip = 1;
	dup2(fd, STDIN_FILENO);
	if (!node->cmd && args[*i + 2] && !is_redir_check(args[*i + 2])
		&& !exec_check(args + 2, envp))
		return (print_err2(args, *i));
	args_left_move(args, *i);
	args_left_move(args, *i);
	*i -= 1;
	close(fd);
	return (0);
}

int	left_double_redir2(char **args, char **envp, int *i, t_node *node)
{
	char	*line[2];

	while (1)
	{
		line[0] = get_line("> ");
		if (!line[0])
			break ;
		line[1] = expand_envvar(line[0], envp);
		free(line[0]);
		ft_putendl_fd(line[1], node->redir_fd);
		if (!ft_strncmp(line[1], args[*i + 1], ft_strlen(args[*i + 1]) + 1))
		{
			free(line[1]);
			break ;
		}
		free(line[1]);
	}
	lseek(node->redir_fd, 0, SEEK_SET);
	dup2(node->redir_fd, STDIN_FILENO);
	close(node->redir_fd);
	if (!node->cmd && args[*i + 2] && !is_redir_check(args[*i + 2])
		&& !exec_check(args + 2, envp))
		return (print_err2(args, *i));
	double_lmove_idx_change(args, i);
	return (unlink(".temp") == -1);
}

int	left_double_redir(char **args, char **envp, int *i, t_node *node)
{
	node->redir_fd = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!args[*i + 1] || !ft_strncmp(args[*i + 1], " ", ft_strlen(args[*i
					+ 1])))
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", STDERR_FILENO);
		ft_putstr_fd("token `newline'\n", STDERR_FILENO);
		return (1);
	}
	return (left_double_redir2(args, envp, i, node));
}

int	right_redir(char **args, char **envp, int *i, t_node *node)
{
	int	fd;

	fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd <= 0)
	{
		if (!node->pipe_idx)
			return (print_err(args, *i, node));
		exit(EXIT_FAILURE);
	}
	node->right_flag = 1;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!node->cmd && args[*i + 2] && !is_redir_check(args[*i + 2])
		&& !exec_check(args + 2, envp))
		return (print_err2(args, *i));
	args_left_move(args, *i);
	args_left_move(args, *i);
	*i -= 1;
	return (0);
}

int	right_double_redir(char **args, char **envp, int *i, t_node *node)
{
	int	fd;

	fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd <= 0)
	{
		if (!node->pipe_idx)
			return (print_err(args, *i, node));
		exit(EXIT_FAILURE);
	}
	node->right_flag = 1;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!node->cmd && args[*i + 2] && !is_redir_check(args[*i + 2])
		&& !exec_check(args + 2, envp))
		return (print_err2(args, *i));
	args_left_move(args, *i);
	args_left_move(args, *i);
	*i -= 1;
	return (0);
}
