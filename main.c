/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:27:22 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_exit_status = 0;

char	**strarradd(char **strs, char *str)
{
	int		i;
	char	**newstrs;

	i = 0;
	while (strs[i])
		i++;
	newstrs = malloc((i + 2) * 8);
	i = -1;
	while (strs[++i])
		newstrs[i] = strs[i];
	newstrs[i++] = ft_strdup(str);
	newstrs[i] = 0;
	free(strs);
	strs = newstrs;
	return (strs);
}

char	**strarrcpy(char **strs)
{
	int		i;
	char	**newstrs;

	i = 0;
	while (strs[i])
		i++;
	newstrs = malloc((i + 1) * 8);
	i = -1;
	while (strs[++i])
		newstrs[i] = ft_strdup(strs[i]);
	newstrs[i] = 0;
	return (newstrs);
}

void	strarrfree(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;

	(void)argc;
	(void)argv;
	envp_copy = strarrcpy(envp);
	set_signal();
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (ft_strncmp(line, "\0", 1))
				parser(line, envp_copy);
		}
		else
			cmd_exit_no_arg();
	}
	return (0);
}
