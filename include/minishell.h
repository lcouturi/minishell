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
# include "../libs/Libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

char	**arg_splitter(char *s);
void	cmd_cd(char **args, char **envp);
void	cmd_echo(char **args, char **envs);
void	cmd_env(char **envs);
void	cmd_exec(char **args, char **envp);
void	cmd_exit(char **args);
void	cmd_pwd(void);
char	*expand_envvar(char *str, char **envp);
void	free_string_array(char **strs);
void	parser(char *str, char **envp);
void	quote_check(char const *s, int *i);

#endif
