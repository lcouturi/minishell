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

int	print_err(char **args, int i, t_node *node)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[i + 1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	g_exit_status = 1;
	if (pipe_check(args, node))
	{
		args_left_move(args, 1);
		args_left_move(args, 0);
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
	if (args[i + 1] == NULL)
	{
		args[i] = NULL;
		free(args[i + 1]);
	}
}

bool	is_redir(char **args, int i, int j)
{
	if (args[i][j] == '<' || args[i][j] == '>')
		return (true);
	return (false);
}

int	print_re_syntax_error()
{
	g_exit_status = 2;
	ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
	ft_putstr_fd("unexpected token `newline'", STDERR_FILENO);
	return (0);
}

int	redir_syntax_check(char **args)
{
	int	i;

	i = -1;
	if (args && args[0] && is_redir(args, 0, 0))
		return (print_re_syntax_error());
	while (args[++i])
	{
		if (args[i + 1] == NULL && (is_redir(args, i, 0)
			|| args[i][0] == '|'))
			return (print_re_syntax_error());
	}
	return (1);
}
