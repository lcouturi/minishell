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
		envp = semicolon_handler(line, envp, node);
	strarrfree(envp);
	exit(g_exit_status);
}

char	*get_line(char *str)
{
	char	*line;
	char	*line2;

	if (isatty(STDIN_FILENO))
		line = readline(str);
	else
	{
		line2 = get_next_line(STDIN_FILENO);
		if (!line2)
			exit(g_exit_status);
		line = ft_strtrim(line2, "\n");
		free(line2);
	}
	return (line);
}

static void	shlvl_plus_plus(char **envp)
{
	char	*str;

	str = ft_itoa(ft_atoi(ft_getenv("SHLVL", envp)) + 1);
	if (!str)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	ft_setenv("SHLVL", str, envp);
	free(str);
}

static void	setpwd(t_node *node, char **envp)
{
	char	*curdir[2];
	int		n;

	curdir[0] = getcwd(0, 0);
	node->pwd = ft_strdup(ft_getenv("PWD", envp));
	if (chdir(node->pwd) == -1)
	{
		free(node->pwd);
		node->pwd = curdir[0];
		return ;
	}
	curdir[1] = getcwd(0, 0);
	if (ft_strlen(curdir[0]) < ft_strlen(curdir[1]))
		n = ft_strlen(curdir[0]) + 1;
	else
		n = ft_strlen(curdir[1]) + 1;
	if (ft_strncmp(curdir[0], curdir[1], n))
	{
		free(node->pwd);
		node->pwd = curdir[0];
		chdir(node->pwd);
	}
	else
		free(curdir[0]);
	free(curdir[1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;
	t_node	node;

	g_exit_status = 0;
	envp_copy = strarrdup(envp);
	setpwd(&node, envp);
	shlvl_plus_plus(envp_copy);
	if (!envp_copy)
		exit(EXIT_FAILURE);
	set_signal();
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 3))
		argmode(argv[2], envp_copy, &node);
	while (1)
	{
		line = get_line("minishell$ ");
		if (!line)
		{
			strarrfree(envp_copy);
			exit(EXIT_FAILURE);
		}
		init_node(&node);
		if (ft_strncmp(line, "\0", 1))
			envp_copy = semicolon_handler(line, envp_copy, &node);
	}
}
