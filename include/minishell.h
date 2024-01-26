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
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	**arg_splitter(char *s);
void	cmd_cd(char **args, char **envp, int *exit_status);
void	cmd_echo(char **args, char **envs, int *exit_status);
void	cmd_env(char **envs);
void	cmd_exec(char **args, char **envp, int *exit_status);
void	cmd_exit(char **args, char **envp);
void	cmd_exit_no_arg(void);
char	**cmd_export(char **args, char **envp);
void	cmd_pwd(void);
void	cmd_unset(char **args, char **envp, int *exit_status);
char	*expand_envvar(char *str, char **envp, int *exit_status);
char	**expand_wildcard(char **args);
int		ft_isspace(char c);
char	**parser(char *str, char **envp, int *exit_status);
void	quote_check(char const *s, int *i);
char	**rm_quotes(char **args);
char	**strarradd(char **strs, char *str);
char	**strarrcpy(char **strs);
void	strarrfree(char **strs);
void	strarrprint(char **strs);
// signal
void	set_signal(void);
// redirection
int		redir_chk(char **args);
int		exec_redir(char **args, char **envp, int fds[]);
void	exec_redir_cmd(char **args, char **envp);
int		left_redir(char **args, int i);
void	left_double_redir(char **args, int i, int **fds);
void	right_redir(char **args, int i);
void	right_double_redir(char **args, int i);

#endif
