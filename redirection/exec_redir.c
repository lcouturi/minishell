/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:48:33 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir_cmd(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &status, WUNTRACED);
}

void	exec_redir(char **args, char **envp, int fds[])
{
	int	i;

	i = -1;
	(void)envp;
	while (args[++i] != NULL)
	{
		if (ft_strncmp(args[i], "<", 2) == 0)
			left_redir(args, i);
		else if (ft_strncmp(args[i], ">", 2) == 0)
			right_redir(args, i);
		else if (ft_strncmp(args[i], ">>", 3) == 0)
			right_double_redir(args, i);
		else if (ft_strncmp(args[i], "<<", 3) == 0)
			left_dobule_redir(args, i, &fds);
	}
}
