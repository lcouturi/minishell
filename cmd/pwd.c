#include "minishell.h"

void	cmd_pwd(void)
{
	char		*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}