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

int	exec_redir(char **args, char **envp, t_node *node)
{
	int	i;

	i = 0;
	while (args[i] != NULL && ft_strncmp(args[i], "|", 2)
		&& node->redir_stop == 0)
	{
		if (ft_strncmp(args[i], "<", 2) == 0)
		{
			if (left_redir(args, i, node))
				return (1);
		}
		else if (ft_strncmp(args[i], ">", 2) == 0)
			right_redir(args, envp, i, node);
		else if (ft_strncmp(args[i], ">>", 3) == 0)
			right_double_redir(args, envp, i, node);
		else if (ft_strncmp(args[i], "<<", 3) == 0)
			if (left_double_redir(args, i))
				return (1);
		i++;
	}
	return (0);
}

void	original_store(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	node->ori_args = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (args[++i])
	{
		node->ori_args[i] = ft_strdup(args[i]);
	}
	node->ori_args[i] = NULL;
}
