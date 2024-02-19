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
	int		i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp("<<", args[i], 3) || !ft_strncmp(">>", args[i], 3)
			|| !ft_strncmp("<", args[i], 2) || !ft_strncmp(">", args[i], 2))
			return (1);
	}
	return (0);
}

void	argu_long(char **args, int k, int len)
{
	free(args[k]);
	free(args[k + 1]);
	args[k + 1] = NULL;
	while (k + 2 < len)
	{
		args[k] = ft_strdup(args[k + 2]);
		free(args[k + 2]);
		args[k + 2] = NULL;
		k++;
	}
}

void	argu_two(char **args, int k)
{
	free(args[k]);
	free(args[k + 1]);
	args[k] = NULL;
	args[k + 1] = NULL;
}

void	argu_left_change(char **args)
{
	int	i;
	int	k;
	int	len;

	i = -1;
	len = strarrlen(args);
	while (args[++i])
	{
		if (ft_strncmp(args[i], "<<", 3) == 0)
		{
			k = i;
			if (k + 1 == len)
			{
				free(args[k]);
				args[k] = NULL;
			}
			else if (k + 2 == len)
				argu_two(args, k);
			else
				argu_long(args, k, len);
		}
	}
}

int	two_redir(char **args, t_node *node)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (args && args[i])
	{
		if (is_redir_check(args[i]))
		{
			if (num == 1)
				node->redir_idx = i;
			num++;
		}
		i++;
	}
	if (num >= 2)
		return (1);
	else
		return (0);
}

void	exec_redir_child(char **args, char **envp, t_node *node, int *flag)
{
	if (node->redir_flag)
	{
		if (node->redir_idx != 0)
		{
			close(node->redir_fds[0]);
			dup2(node->redir_fds[1], STDOUT_FILENO);
			close(node->redir_fds[1]);
			if (exec_redir(args, envp, node))
				*flag = 1;
			exit(g_exit_status);
		}
		else
		{
			if (exec_redir(args, envp, node))
				*flag = 1;
		}
	}
}

void	exec_redir_parents(char **args, char **envp, t_node *node, int *flag)
{
	int status;

	waitpid(-1, &status, 0);
	close(node->redir_fds[1]);
	dup2(node->redir_fds[0], STDIN_FILENO);
	close(node->redir_fds[0]);
	if (exec_redir(args, envp, node))
		*flag = 1;
}

bool	is_redir_check(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0
	|| ft_strncmp(str, ">", 2) == 0
	|| ft_strncmp(str, ">>", 3) == 0
	|| ft_strncmp(str, "<<", 3) == 0)
		return (true);
	return (false);
}

int	redir_excute(char **args, char **envp, t_node *node)
{
	int	pid;
	int	flag;

	pid = 0;
	flag = 0;
	if (two_redir(args, node))
	{
		pipe(node->redir_fds);
		pid = fork();
		if (pid < 0)
			return (1);
	}
	if (node->redir_flag)
	{
		if (pid == 0) {
			if (node->redir_idx != 0)
				args[node->redir_idx] = 0;
			exec_redir_child(args, envp, node, &flag);
		}
		else
			exec_redir_parents(args + node->redir_idx, envp, node, &flag);
	}
	return (flag);
}
