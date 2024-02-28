/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/27 09:21:21 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_operator(char **args, int i)
{
	return (!ft_strncmp(args[i], "|", 2) || !ft_strncmp(args[i], "||", 3));
}

static int	print_syntax_error(char **args, int i, int j)
{
	g_exit_status = 2;
	ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
	ft_putstr_fd("near unexpected token `", STDERR_FILENO);
	if (args[i][j] == '|' && (!args[i][j + 1] || args[i][j + 1] != '|'))
		ft_putstr_fd("|", STDERR_FILENO);
	else if (args[i][j] == '&' && (!args[i][j + 1] || args[i][j + 1] != '&'))
		ft_putstr_fd("&", STDERR_FILENO);
	else if (args[i][j] == '|' && args[i][j + 1] && args[i][j + 1] == '|')
		ft_putstr_fd("||", STDERR_FILENO);
	else if (args[i][j] == '&' && args[i][j + 1] && args[i][j + 1] == '&')
		ft_putstr_fd("&&", STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (0);
}

int	pipe_syntax_check(char **args)
{
	int	i;

	i = -1;
	if (args && args[0] && args[0][0] == '|')
		return (print_syntax_error(args, 0, 0));
	while (args[++i])
	{
		if (args[i + 1] && is_operator(args, i) && is_operator(args, i + 1))
			return (print_syntax_error(args, i, 0));
		if (args[i][1] && args[i][0] == '|' && args[i][1] == '|'
			&& args[i][0] != args[i][1])
			return (print_syntax_error(args, i, 1));
		if (args[i][1] && args[i][2] && args[i][1] == '|' && args[i][2] == '|')
			return (print_syntax_error(args, i, 2));
	}
	return (1);
}

char	**one_commnad(char **args, char **envp, t_node *node)
{
	envp = find_command(args, envp, node);
	if (node->redir_flag)
		backup_restor(node);
	return (envp);
}
