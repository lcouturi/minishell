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

void	cmd_exit(char **args, char **envp)
{
	unsigned char	exit_status;

	g_exit_status = EXIT_SUCCESS;
	if (strarrlen(args) > 1)
	{
		exit_status = ft_atoi(args[1]);
		g_exit_status = exit_status;
	}
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
