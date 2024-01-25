/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:07 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_chk(char **args)
{
	size_t	str_len;
	int		i;

	i = -1;
	(void)str_len;
	while (args[++i])
	{
		str_len = ft_strlen(args[i]);
		if (!ft_strncmp("<<", args[i], 3)
			|| !ft_strncmp(">>", args[i], 3)
			|| !ft_strncmp("<", args[i], 2)
			||!ft_strncmp(">", args[i], 2))
			return (1);
	}
	return (0);
}

void	exec_child(char **args, char **envp, int fds[], int *exit_status)
{
	(void)envp;
	(void)args;
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	// execute
	exit(*exit_status);
}

void	exec_parents(int pid, int fds[], int *exit_status)
{
	int	status;

	close(fds[1]);
	close(fds[0]);
	waitpid(pid, &status, 0);
	*exit_status = status >> 8;
}
