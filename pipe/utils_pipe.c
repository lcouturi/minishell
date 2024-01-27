#include "../include/minishell.h"

void	exec_child(char **args, char **envp, t_node *node)
{
	(void)envp;
	(void)args;
	close(node->fds[1]);
	dup2(node->fds[0], STDIN_FILENO);
	close(node->fds[0]);
	execute(args + node->pipe_idx, envp, node);
	exit(node->exit_status);
}

void	exec_parents(int pid, t_node *node)
{
	int	status;

	close(node->fds[1]);
	close(node->fds[0]);
	waitpid(pid, &status, 0);
	node->exit_status = status >> 8;
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

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
		{
			node->pipe_idx = i + 1;
			node->pipe_flag = 1;
			return (1);
		}
		i++;
	}
	node->pipe_flag = 0;
	return (0);
}

void	init_node(t_node *node)
{
	node->pipe_idx = 0;
}
