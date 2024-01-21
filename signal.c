
#include "include/minishell.h"

/*
	signal(SIGINT, handle_signal); -> ctrl + c
	signal(SIGQUIT, handle_signal); -> ctrl + '\'
*/

void	handle_signal(int signum)
{
	pid_t	pid;
	int		status;
	char	*line;

	pid = waitpid(-1, &status, WNOHANG);
	(void)line;
	if (signum == SIGINT)
	{
		printf("SIGINT\n");
		if (pid == -1)
		{
			ft_putstr_fd("\b\b  \b\b\n", STDOUT);
			line = readline("minishell> ");
			g_exit_status = 1;
		}
		else
			ft_putchar_fd('\n', STDOUT);
	}
	else if (signum == SIGQUIT)
	{
		printf("SIGOUT\n");
		if (pid == -1)
			ft_putstr_fd("\b\b  \b\b", STDOUT);
		else
			ft_putstr_fd("Quit: \n", STDOUT);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);//ctrl + c
	signal(SIGQUIT, handle_signal);//ctrl + '\'
}