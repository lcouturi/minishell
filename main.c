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

static void	argmode(char *arg, char **envp, t_node *node)
{
	char	*line;

	line = ft_strdup(arg);
	if (!line)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	init_node(node);
	if (ft_strncmp(line, "\0", 1))
		envp = parser(line, envp, node);
	strarrfree(envp);
	exit(g_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;
	t_node	node;

	g_exit_status = 0;
	envp_copy = strarrdup(envp);
	if (!envp_copy)
		exit(EXIT_FAILURE);
	set_signal();
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 3))
		argmode(argv[2], envp_copy, &node);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			strarrfree(envp_copy);
			exit(EXIT_FAILURE);
		}
		init_node(&node);
		if (ft_strncmp(line, "\0", 1))
			envp_copy = parser(line, envp_copy, &node);
	}
}
