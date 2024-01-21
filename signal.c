
#include "include/minishell.h"

/*
	signal(SIGINT, handle_signal); -> ctrl + c
	signal(SIGQUIT, handle_signal); -> ctrl + '\'
*/

void	handle_signal(int signo)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT){
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \n",STDOUT);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", STDOUT);
	}
	else if(signo == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", STDOUT);
		}
		else
			ft_putstr_fd("Quit: \n", STDOUT);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}