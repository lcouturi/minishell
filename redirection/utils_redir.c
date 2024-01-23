#include "../include/minishell.h"

int	redir_chk(char **args)
{
	size_t	str_len;
	int		i;

	i = -1;
	while (args[++i])
	{
		str_len = ft_strlen(args[i]);
		if (!ft_strncmp("<<", args[i], str_len)
			|| !ft_strncmp(">>", args[i], str_len)
			|| !ft_strncmp("<", args[i], str_len)
			||!ft_strncmp(">", args[i], str_len))
			return (1);
	}
	return (0);
}
