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
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

char	*change_args(char *args)
{
	(void)args; // to_do_list
	return NULL;
}

void	cmd_echo_envv(char **args, char **envp, int i)
{
	if (args[i][0] == '$' && args[1][1] == '?') // but also need to care any other idx too..
		printf("0\n"); // to_do_list
	else
		printf("1\n");
	// to_ do_liset
	(void)envp;
}

void	cmd_echo(char **args, char **envp)
{
	int		i;
	int		new_line;
	char	cha;

	i = 1;
	new_line = 1;
	cha = '\'';
	while (is_n_option(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		if (ft_strchr(args[i], cha))
			args[i] = change_args(args[i]);
		if (args[i][0] == '$')
			cmd_echo_envv(args, envp, i);
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		printf("\n");
}
