#include "minishell.h"

void	cmd_env(char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
		printf("%s\n", envs[i]);
}