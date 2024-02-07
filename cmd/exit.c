/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:27:22 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdbool.h>

static bool	error_check(char **args, bool num, int i)
{
	if (strarrlen(args) > 1)
	{
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]) && !(!i && (args[1][i] == '-'
						|| args[1][i] == '+')))
			{
				num = 1;
				g_exit_status = 2;
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(args[1], 2);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				break ;
			}
		}
	}
	if (!num && strarrlen(args) > 2)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	cmd_exit(char **args, char **envp)
{
	unsigned char	exit_status;

	printf("exit\n");
	g_exit_status = EXIT_SUCCESS;
	if (strarrlen(args) > 1)
	{
		exit_status = ft_atoi(args[1]);
		g_exit_status = exit_status;
	}
	if (error_check(args, 0, -1))
		return ;
	strarrfree(args);
	strarrfree(envp);
	rl_clear_history();
	exit(g_exit_status);
}

void	cmd_exit_no_arg(void)
{
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
