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

void	free_string_array(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

static void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
}

static char	*whitespace_hack(char *s)
{
	int	i;

	i = -1;
	while (++i)
		if (s[i] == 9 || s[i] == 10 || s[i] == 11 || s[i] == 12 || s[i] == 13)
			s[i] = ' ';
	return (s);
}

static void	parser(char *str, char **envp)
{
	char	**args;

	args = ft_split(whitespace_hack(str), ' ');
	if (!args)
	{
		free(str);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	if (args[0])
	{
		if (!ft_strncmp(args[0], "cd", 3))
			cmd_cd(args, envp);
		else if (!ft_strncmp(args[0], "exit", 5))
			cmd_exit(args);
		else if (!ft_strncmp(args[0], "env", 4))
			cmd_env(envp);
		else if (!ft_strncmp(args[0], "pwd", 4))
			cmd_pwd();
		else if (!ft_strncmp(args[0], "echo", 5))
			cmd_echo(args, envp);
		else
			cmd_exec(args, envp);
	}
	add_history(str);
	free(str);
	free_string_array(args);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (ft_strncmp(line, "\0", 1))
				parser(line, envp);
		}
		else
			printf("ctrl + d\n");
	}
	return (0);
}
