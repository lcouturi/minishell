/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/21 19:03:14 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/*
	signal(SIGINT, handle_signal); -> ctrl + c
	signal(SIGQUIT, handle_signal); -> ctrl + '\'
*/

void	sigint(void)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	sigquit(void)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	g_exit_status = 0;
}

void	handle_signal(int signo)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
			sigint();
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			sigquit();
		else
			ft_putstr_fd("Quit: \n", STDOUT_FILENO);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
