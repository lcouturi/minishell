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

char	**cloturn(int backup_stdout, int backup_stdin, char **envp)
{
	close(backup_stdout);
	close(backup_stdin);
	return (envp);
}

int	pipe_check(char **args, t_node *node)
{
	int	i;

	i = node->pipe_idx;
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_node(t_node *node)
{
	node->pipe_idx = 0;
}
