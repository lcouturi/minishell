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
		cmd_exit(args, envp);
	else if (!ft_strncmp(args[0], "env", 4))
		cmd_env(envp);
	else if (!ft_strncmp(args[0], "export", 7))
		cmd_export(args, envp);
	else if (!ft_strncmp(args[0], "pwd", 4))
		cmd_pwd();
	else if (!ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, envp);
	else if (!ft_strncmp(args[0], "unset", 6))
		cmd_unset(args, envp);
	else
		cmd_exec(args, envp);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	execute(char **args, char **envp, int fds[], int flag)
{
	int	backup_stdout;
	int	backup_stdin;

	backup_stdout = dup(STDOUT_FILENO);
	backup_stdin = dup(STDIN_FILENO);
	if (flag)
		exec_redir(args, envp, fds);
	if (args[0])
		find_command(args, envp);
	dup2(backup_stdout, STDOUT_FILENO);
	dup2(backup_stdin, STDIN_FILENO);
	close(backup_stdout);
	close(backup_stdin);
}

void	parser(char *str, char **envp)
{
	char	**args;
	int		fds[2];
	int		flag;

	args = arg_splitter(expand_envvar(str, envp));
	flag = redir_chk(args);
	args = rm_quotes(args);
	add_history(str);
	free(str);
	if (!args)
	{
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	// pipe(fds);
	execute(args, envp, fds, flag);
	strarrfree(args);
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
