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
	if (!pid)
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
	int	ret;

	i = -1;
	ret = 0;
	if (exec_check(args, envp))
		node->cmd = ft_strdup(args[0]);
	while (args[++i] && ft_strncmp(args[i], "|", 2)
		&& !node->redir_stop && ret == 0)
	{
		if (!ft_strncmp(args[i], "<", 2))
			ret = left_redir(args, envp, &i, node);
		else if (!ft_strncmp(args[i], ">", 2))
			ret = right_redir(args, envp, &i, node);
		else if (!ft_strncmp(args[i], ">>", 3))
			ret = right_double_redir(args, envp, &i, node);
		else if (!ft_strncmp(args[i], "<<", 3))
			ret = left_double_redir(args, envp, &i, node);
	}
	return (ret);
}

void	args_left_move_i(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (++i < node->redir_idx)
		args_left_move(args, 1);
}

int	print_err2(char **args, int i)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[i + 2], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	return (1);
}
