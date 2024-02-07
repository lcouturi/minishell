/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:46:47 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_key(char *key)
{
	int	i;

	i = -1;
	if (ft_strlen(key) == 0)
		return (0);
	if (ft_isdigit(key[0]))
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}

int	find_envkey(char *str, char *envp)
{
	int	i;

	i = 0;
	while (str[i] && envp[i] && (str[i] == envp[i]) && (envp[i] != '='))
		i++;
	if ((str[i] == '\0') && (envp[i] == '='))
		return (1);
	return (0);
}

int	delete_env(char *str, char **envp)
{
	int	i;
	int	last;

	last = 0;
	while ((envp[last]) != NULL)
		last++;
	if (last < 1)
		return (0);
	i = -1;
	while (envp[++i] != NULL)
	{
		if (find_envkey(str, envp[i]))
		{
			free(envp[i]);
			envp[i] = ft_strdup(envp[last - 1]);
			free(envp[last - 1]);
			envp[last - 1] = NULL;
			return (1);
		}
	}
	return (1);
}

void	cmd_unset(char **args, char **envp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (args[++i])
	{
		if (valid_key(args[i]) == 0)
		{
			printf("minishell: unset : `%s\'", args[i]);
			printf(": not a valid identifier\n");
			flag = 0;
		}
	}
	if (flag)
	{
		i = 0;
		while (args[++i])
			flag = delete_env(args[i], envp);
		if (flag != 1)
			g_exit_status = EXIT_FAILURE;
		else
			g_exit_status = EXIT_SUCCESS;
	}
}
