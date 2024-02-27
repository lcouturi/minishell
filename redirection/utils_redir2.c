/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:07 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_err(char **args, int i, t_node *node)
{
	errno = ENOENT;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(args[i + 1]);
	g_exit_status = 1;
	node->parent_die = 1;
	if (pipe_check(args, node))
	{
		if (!ft_strncmp(args[i + 1], "|", 2))
			node->redir_stop = 1;
		args_left_move(args, 1);
		if (!ft_strncmp(args[i + 1], "|", 2))
			node->redir_stop = 1;
		args_left_move(args, 0);
		if (!ft_strncmp(args[i + 1], "|", 2))
			node->redir_stop = 1;
		node->child_die = 1;
		return (0);
	}
	return (1);
}

void	args_left_move(char **args, int i)
{
	while (args[i] && args[i + 1])
	{
		free(args[i]);
		args[i] = ft_strdup(args[i + 1]);
		i++;
	}
	if (!args[i + 1])
	{
		args[i] = NULL;
		free(args[i + 1]);
	}
}

bool	is_redir(char **args, int i, int j)
{
	return (args && args[i] && (args[i][j] == '<' || args[i][j] == '>'));
}

int	print_re_syntax_error(void)
{
	g_exit_status = 2;
	ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
	ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
	return (0);
}

int	redir_syntax_check(char **args)
{
	int	i;

	i = -1;
	if (args && args[0] && is_redir(args, 0, 0) && !args[i + 1])
		return (print_re_syntax_error());
	while (args[++i])
		if (args[i][0] != '\'' && args[i][0] != '\"' && !args[i + 1]
			&& is_redir(args, i, 0))
			return (print_re_syntax_error());
	return (1);
}
