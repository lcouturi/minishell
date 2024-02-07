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

char	**find_command(char **args, char **envp, t_node *node)
{
	if (!ft_strncmp(args[0], "cd", 3))
		cmd_cd(args, envp);
	else if (!ft_strncmp(args[0], "exit", 5))
		cmd_exit(args, envp);
	else if (!ft_strncmp(args[0], "env", 4))
		cmd_env(envp);
	else if (!ft_strncmp(args[0], "export", 7))
		envp = cmd_export(args, envp);
	else if (!ft_strncmp(args[0], "pwd", 4))
		cmd_pwd();
	else if (!ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, envp, node);
	else if (!ft_strncmp(args[0], "unset", 6))
		cmd_unset(args, envp);
	else
		cmd_exec(args, envp, node);
	return (envp);
}

char	**parser(char *str, char **envp, t_node *node)
{
	char	**args;
	int		i;

	args = expand_wildcard(arg_splitter(expand_envvar(str, envp)));
	i = -1;
	add_history(str);
	free(str);
	if (!args[0])
	{
		strarrfree(args);
		return (envp);
	}
	node->redir_flag = redir_chk(args);
	args = rm_quotes(args, node);
	if (!args)
	{
		rl_clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node);
	strarrfree(args);
	return (envp);
}

void	quote_check(char const *s, int *i)
{
	int	j;

	i[3] = 0;
	i[4] = 0;
	j = 0;
	while (j <= i[0])
	{
		if (!i[4] && s[j] == '\"')
		{
			if (!i[3])
				i[3] = 1;
			else
				i[3] = 0;
		}
		if (!i[3] && s[j] == '\'')
		{
			if (!i[4])
				i[4] = 1;
			else
				i[4] = 0;
		}
		j++;
	}
}
