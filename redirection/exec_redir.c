#include "../include/minishell.h"

void	exec_redir_cmd(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &status, WUNTRACED);
}

void	exec_redir(char **args, int pipe_check)
{
	int	i;
	int	saved_stdout;
	int	saved_stdin;

	(void)pipe_check;
	i = -1;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	while (args[++i] != NULL)
	{
		if (strcmp(args[i], "<") == 0)
			left_redir(args, i);
		else if (strcmp(args[i], ">") == 0)
			right_redir(args, i);
		else if (strcmp(args[i], ">>") == 0)
			right_double_redir(args, i);
		else if (strcmp(args[i], "<<") == 0)
			left_dobule_redir(args, i);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
}
