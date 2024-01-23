#include "../include/minishell.h"

void	exec_redir_cmd(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == 0)
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
	int	fd;

	(void)pipe_check;
	i = -1;
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);
	while (args[++i] != NULL)
	{
		if (strcmp(args[i], "<") == 0)
		{
			args[i] = NULL;
			fd = open(args[i + 1], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (strcmp(args[i], ">") == 0)
		{
			args[i] = NULL;
			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(args[i], ">>") == 0)
		{
			args[i] = NULL;
			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(args[i], "<<") == 0)
		{
			// [To-do-list] need to handle pipe
			(void)i;
		}
	}
	// Restore file descriptors
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
}