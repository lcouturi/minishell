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
# include <errno.h>
# include <fcntl.h>
# include "../libs/Libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node
{
	int		redir_flag;
	int		pipe_flag;
	int		backup_stdout;
	int		backup_stdin;
	int		pipe_idx;
	int		fds[2];
	int		i;
	char	*path;
	int		quota_pipe_idx_arr[10];
	int		quota_pipe_cnt;
	int		quota_idx_j;
	int		echo_skip;
	char	**ori_args;
	int		child_die;
}	t_node;

int		g_exit_status;

char	**arg_splitter(char *s);
char	**escape_split(char *s, char c);
void	cmd_cd(char **args, char **envp);
void	cmd_echo(char **args, t_node *node);
void	cmd_env(char **envs);
void	cmd_exec(char **args, char **envp, t_node *node);
void	cmd_exit(char **args, char **envp);
void	cmd_exit_no_arg(void);
char	**cmd_export(char **args, char **envp);
void	cmd_pwd(char **envp);
void	cmd_unset(char **args, char **envp);
bool	exec_check(char **args, char **envp);
void	exec_proc(char **args, char **envp, t_node *node);
char	*expand_envvar(char *str, char **envp);
char	**expand_wildcard(char **args);
char	*ft_getenv(const char *name, char **envp);
int		ft_isenv(char c);
int		ft_isspace(char c);
int		ft_setenv(const char *name, const char *value, char **envp);
int		get_arg_num(char **args);
char	**get_file_list(bool hidden);
void	get_length(char *str, char **envp, int *i);
int		isop(char c);
char	**load_lst(struct dirent *dr, DIR *dir, bool hidden);
void	match(char *str, char **split, char **files, int i);
char	**execute(char **args, char **envp, t_node *node);
void	quote_check(char const *s, int *i);
char	**rm_quotes(char **args, t_node *node);
char	**semicolon_handler(char *str, char **envp, t_node *node);
char	**strarradd(char **strs, char *str);
char	**strarrdup(char **strs);
void	strarrfree(char **strs);
size_t	strarrlen(char **strs);
void	strarrprint(char **strs);
char	**find_command(char **args, char **envp, t_node *node);
char	**rm_quotes_wildcards(char **args);
// signal
void	set_signal(void);
// redirection
int		redir_chk(char **args);
int		exec_redir(char **args, char **envp, t_node *node);
void	exec_redir_cmd(char **args, char **envp);
int		left_redir(char **args, int i, t_node *node);
int		left_double_redir(char **args, int i);
void	right_redir(char **args, char **envp, int i);
void	right_double_redir(char **args, char **envp, int i);
void	argu_left_change(char **args);
int		redir_excute(char **args, char **envp, t_node *node);
int		repeat_check(char **args, t_node *node);
void	original_store(char **args, t_node *node);
void	args_left_move(char **args, int i);
int		print_err(char **args, int i, t_node *node);
// pipe
void	exec_child(char **args, char **envp, t_node *node);
void	exec_parents(int pid, char **args, char **envp, t_node *node);
char	**cloturn(int backup_stdout, int backup_stdin, char **envp);
int		pipe_check(char **args, t_node *node);
void	init_node(t_node *node);
void	backup_restor(t_node *node);
char	**split_before_pipe_args(char **args, t_node *node);
char	**repeat(char **args, char **envp, t_node *node);
void	print_from_fd(int fd);

#endif
