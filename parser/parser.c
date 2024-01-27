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

static char	**find_command(char **args, char **envp, int *exit_status)
{
	//printf("find_command실행 : %s\n", args[0]);
	if (!ft_strncmp(args[0], "cd", 3))
		cmd_cd(args, envp, exit_status);
	else if (!ft_strncmp(args[0], "exit", 5))
		cmd_exit(args, envp);
	else if (!ft_strncmp(args[0], "env", 4))
		cmd_env(envp);
	else if (!ft_strncmp(args[0], "export", 7))
		envp = cmd_export(args, envp);
	else if (!ft_strncmp(args[0], "pwd", 4))
		cmd_pwd();
	else if (!ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, envp, exit_status);
	else if (!ft_strncmp(args[0], "unset", 6))
		cmd_unset(args, envp, exit_status);
	else
		cmd_exec(args, envp, exit_status);
	return (envp);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	**execute(char **args, char **envp, t_node *node, int *exit_status)
{
	int	pid;

	pipe(node->fds);
	node->backup_stdout = dup(STDOUT_FILENO);
	node->backup_stdin = dup(STDIN_FILENO);
	pid = 0;
	if (node->redir_flag)
	{
		if (exec_redir(args, envp, node->fds))
			return (cloturn(node->backup_stdout, node->backup_stdin, envp));
	}
	if (pipe_check(args, node))
	{
		pid = fork();
		if (pid < 0)
			return (cloturn(node->backup_stdout, node->backup_stdin, envp));
		// node->fds[0] = dup(STDOUT_FILENO);
		// node->fds[1] = dup(STDIN_FILENO);
	}
	else
	{
		envp = find_command(args, envp, exit_status);
		
		if (node->redir_flag == 0)
			return (cloturn(node->backup_stdout, node->backup_stdin, envp));
		else
		{
			dup2(node->backup_stdout, STDOUT_FILENO);
			dup2(node->backup_stdin, STDIN_FILENO);
			return (cloturn(node->backup_stdout, node->backup_stdin, envp));
		}
	}
	if (pid == 0 && args[0])
	{
		envp = find_command(args, envp, exit_status);
		exec_child(args, envp, node, exit_status);
	}
	else
	{
		exec_parents(pid, node, exit_status);
	}
	dup2(node->backup_stdout, STDOUT_FILENO);
	dup2(node->backup_stdin, STDIN_FILENO);
	return (cloturn(node->backup_stdout, node->backup_stdin, envp));
}

char	**parser(char *str, char **envp, int *exit_status, t_node *node)
{
	char	**args;

	args = expand_wildcard(arg_splitter(expand_envvar(str, envp, exit_status)));
	node->redir_flag = redir_chk(args);
	args = rm_quotes(args);
	add_history(str);
	free(str);
	if (!args)
	{
		rl_clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node, exit_status);
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
