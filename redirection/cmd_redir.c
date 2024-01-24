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

void	left_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_RDONLY, 0744);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	left_dobule_redir(char **args, int i, int **fds)
{
	char	*line;

	line = readline("minishell> ");
	while (ft_strncmp((line), args[i + 1], 5))
	{
		ft_putendl_fd(line, (*fds)[1]);
	}
	close((*fds)[1]);
	dup2((*fds)[0], 0);
	close((*fds)[0]);
	pipe((*fds));
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
