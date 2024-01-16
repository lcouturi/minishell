/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 18:17:38 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("ctrl + c\n");
	rl_on_new_line();
	//rl_replace_line("", 1);
	rl_redisplay();
}

static void	parser(char *str)
{
	char	**args;
	int		i;

	args = ft_split(str, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	i = -1;
	if (!ft_strncmp(args[0], "exit\0", 5))
	{
		while (args[++i])
			free(args[i]);
		free(args);
		exit(EXIT_SUCCESS);
	}
	else
		printf("minishell: %s: command not found\n", args[0]);
	while (args[++i])
		free(args[i]);
	free(args);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	ret = 1;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("input> ");
		if (line)
		{
			if (ft_strncmp(line, "\0", 1))
				parser(line);
			add_history(line);
			free(line);
			line = NULL;
		}
		else
		{
			printf("ctrl + d\n");
		}
	}
	return (0);
}
