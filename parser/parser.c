/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/17 18:12:44 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	find_command(char **args, char **envp)
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

void	parser(char *str, char **envp)
{
	char	**args;

	args = arg_splitter(str);
	add_history(str);
	free(str);
	if (!args)
	{
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	if (args[0])
		find_command(args, envp);
	free_string_array(args);
}
