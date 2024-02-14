/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/17 17:36:28 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_n_option(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 1;
	while (str && str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	cmd_echo(char **args, t_node *node)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 1;
	while (args[++i] && is_n_option(args[i]))
		new_line = 0;
	if (args[i] && !node->echo_skip)
	{
		while (args && args[i])
		{
			if (node->pipe_flag && node->pipe_idx <= i + 1)
				break ;
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (new_line && !(node->pipe_flag))
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = EXIT_SUCCESS;
}
