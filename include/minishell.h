/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/16 22:27:22 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include "../libs/Libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	**arg_splitter(char *s);
void	cmd_cd(char **args, char **envp);
void	cmd_echo(char **args, char **envs);
void	cmd_env(char **envs);
void	cmd_exec(char **args, char **envp, int pipe_check);
void	cmd_exit(char **args, char **envp);
void	cmd_exit_no_arg(void);
void	cmd_pwd(void);
char	*expand_envvar(char *str, char **envp);
char	*expand_wildcard(char *str);
void	free_string_array(char **strs);
int		ft_isspace(char c);
void	parser(char *str, char **envp);
void	quote_check(char const *s, int *i);
// signal
void	set_signal(void);
// redirection
int		redir_chk(char **args);
void	exec_redir(char **args, int pipe_check);
void	exec_redir_cmd(char **args, char **envp);
void	left_redir(char **args, int i);
void	left_dobule_redir(char **args, int i);
void	right_redir(char **args, int i);
void	right_double_redir(char **args, int i);

extern int		g_exit_status;

#endif
