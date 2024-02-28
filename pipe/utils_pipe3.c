/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/27 09:21:21 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_from_fd(int fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
			exit(EXIT_FAILURE);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
		exit(EXIT_FAILURE);
}

int	repeat_check(char **args, t_node *node)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "|", 2))
		{
			if (node->quota_idx_j < node->quota_pipe_cnt
				&& node->quota_pipe_idx_arr[node->quota_idx_j] == i)
				node->quota_idx_j++;
			else
				return (1);
		}
	}
	return (0);
}

void	pipe_work(int pid, char **args, char **envp, t_node *node)
{
	if (!pid)
		exec_child(args, envp, node);
	else
		exec_parents(args, strarrdup(envp), node);
}
