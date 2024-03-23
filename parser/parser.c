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
	if (args[0] && !ft_strncmp(args[0], "cd", 3))
		envp = cmd_cd(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "exit", 5))
		cmd_exit(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "env", 4))
		cmd_env(envp);
	else if (args[0] && !ft_strncmp(args[0], "export", 7))
		envp = cmd_export(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "pwd", 4))
		cmd_pwd(node);
	else if (args[0] && !ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, node);
	else if (args[0] && !ft_strncmp(args[0], "unset", 6))
		cmd_unset(args, envp);
	else if (args[0])
		cmd_exec(args, envp, node);
	return (envp);
}

static char	**parser(char *str, char **envp, t_node *node)
{
	char	**args;

	args = expand_wildcard(escape_split(expand_envvar(str, envp), " \t"), envp);
	free(str);
	if (!args[0])
	{
		strarrfree(args);
		return (envp);
	}
	node->ori_args = strarrdup(args);
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

static void	quote_check_loop(char const *s, int *i, int j, bool *backslash)
{
	if (*backslash)
	{
		*backslash = false;
		i[3] = 3;
		if (j != i[0])
			i[3] = 0;
	}
	else if (i[3] != 2 && s[j] == '\"' && !*backslash)
	{
		if (i[3] == 1)
			i[3] = 0;
		else
			i[3] = 1;
	}
	else if (i[3] != 1 && s[j] == '\'' && !*backslash)
	{
		if (i[3] == 2)
			i[3] = 0;
		else
			i[3] = 2;
	}
	else if (!i[3] && s[j] == '\\')
		*backslash = true;
}

void	quote_check(char const *s, int *i)
{
	bool	backslash;
	int		j;

	backslash = false;
	i[3] = 0;
	j = -1;
	while (++j <= i[0])
		quote_check_loop(s, i, j, &backslash);
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
