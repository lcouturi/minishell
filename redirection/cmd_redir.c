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

void	args_left_move(char **args, int i)
{
	while (args[i] && args[i + 1])
	{
		free(args[i]);
		args[i] = ft_strdup(args[i + 1]);
		i++;
	}
	if (args[i + 1] == NULL)
	{
		args[i] = NULL;
		free(args[i + 1]);
	}
}

int	left_redir(char **args, int i)
{
	int	fd;

	if (access(args[i + 1], R_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[i + 1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	fd = open(args[i + 1], O_RDONLY, 0744);
	if (fd <= 0)
		return (1);
	if (ft_strncmp(args[0], "echo", 5) == 0
		|| ft_strncmp(args[0], "cat", 4) == 0)
	{
		args_left_move(args, i);
		args_left_move(args, i);
	}
	else
		args[i] = NULL;
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	left_double_redir(char **args, int i)
{
	char	*line;
	int		fd;

	fd = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (args[i + 1] == NULL || ft_strncmp(args[i + 1], " ", ft_strlen(args[i
					+ 1]) == 0))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	line = readline("> ");
	while (ft_strncmp((line), args[i + 1], ft_strlen(args[i + 1]) + 1))
	{
		ft_putendl_fd(line, fd);
		line = readline("> ");
	}
	lseek(fd, 0, SEEK_SET);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (unlink(".temp") != 0)
		return (1);
	return (0);
}

void	right_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	right_double_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
