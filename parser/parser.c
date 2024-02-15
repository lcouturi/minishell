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
		cmd_pwd(envp);
	else if (!ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, node);
	else if (!ft_strncmp(args[0], "unset", 6))
		cmd_unset(args, envp);
	else
		cmd_exec(args, envp, node);
	return (envp);
}

static char	**parser(char *str, char **envp, t_node *node)
{
	char	**args;

	args = expand_wildcard(escape_split2(expand_envvar(escape(str), envp),
				" \t\n"));
	free(str);
	if (!args[0])
	{
		strarrfree(args);
		return (envp);
	}
	original_store(args, node);
	args = rm_quotes(args, node);
	if (!args)
	{
		rl_clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node);
	strarrfree(args);
	strarrfree(node->ori_args);
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

char	**semicolon_handler(char *str, char **envp, t_node *node)
{
	int		i;
	char	**split;

	i = -1;
	add_history(str);
	split = escape_split(str, ";");
	while (split[++i])
		envp = parser(split[i], envp, node);
	free(split);
	return (envp);
}
