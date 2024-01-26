#include "../include/minishell.h"

void	exec_child(char **args, char **envp, int fds[], int *exit_status)
{
	(void)envp;
	(void)args;
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	// execute
	exit(*exit_status);
}

void	exec_parents(int pid, int fds[], int *exit_status)
{
	int	status;

	close(fds[1]);
	close(fds[0]);
	waitpid(pid, &status, 0);
	*exit_status = status >> 8;
}

char	**close_backup_return_envp(int backup_stdout, int backup_stdin, char **envp)
{
	close(backup_stdout);
	close(backup_stdin);
	return (envp);
}