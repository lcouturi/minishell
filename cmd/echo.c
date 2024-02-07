/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/17 17:36:28 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_n_option(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 1;
	while (str && str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	change_args(char *args, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args && args[i])
	{
		if (args[i] != c)
			args[j++] = args[i];
		i++;
	}
	args[j] = '\0';
}

char	*find_value(char *key, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
	}
	return ("");
}

void	cmd_echo(char **args, char **envp, t_node *node)
{
	int	i;
	int	new_line;

	(void)envp;
	i = 0;
	new_line = 1;
	while (is_n_option(args[++i]))
		new_line = 0;
	while (args && args[i])
	{
		if (node->pipe_flag && node->pipe_idx <= i + 1)
			break ;
		if (args[i][0] == '\'')
			change_args(args[i], '\'');
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line && !(node->pipe_flag))
		ft_putchar_fd('\n', 1);
	g_exit_status = EXIT_SUCCESS;
}
