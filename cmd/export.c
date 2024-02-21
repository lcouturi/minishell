/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:53:05 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	failure(char *arg, int i)
{
	if (!arg[0] || arg[0] == '=' || ft_isdigit(arg[0]) || (!ft_isalnum(arg[i])
			&& arg[i] != '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

static char	**cmd_export_loop(char *arg, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arg[0] == '=' || ft_isdigit(arg[0]) || arg[++i] != '=')
		if ((i > 0 && !arg[i]) || failure(arg, i))
			return (envp);
	while (ft_strncmp(envp[j], arg, i + 1))
		j++;
	if (!envp[j])
		envp = strarradd(envp, arg);
	else
	{
		free(envp[j]);
		envp[j] = ft_strdup(arg);
	}
	return (envp);
}

static void	printenv(char *str)
{
	int	i;

	i = -1;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (str[++i - 1] != '=')
		ft_putchar_fd(str[i], STDOUT_FILENO);
	ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putstr_fd(str + i, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

static char	**export_print(char **envp)
{
	int		i;
	size_t	i2;
	char	*lowest;
	char	*lowest_old;

	i2 = -1;
	while (++i2 < strarrlen(envp))
	{
		lowest = 0;
		i = -1;
		while (envp[++i])
			if ((!lowest || ft_strncmp(envp[i], lowest, ft_strlen(envp[i])) < 0)
				&& (!i2 || ft_strncmp(envp[i], lowest_old,
						ft_strlen(envp[i])) > 0))
				lowest = envp[i];
		if (ft_strncmp(lowest, "_=", 2))
			printenv(lowest);
		lowest_old = lowest;
	}
	return (envp);
}

char	**cmd_export(char **args, char **envp)
{
	int	i;

	g_exit_status = EXIT_SUCCESS;
	i = -1;
	if (!args[1])
		return (export_print(envp));
	else if (args[1][0] == '-')
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\nexport: usage: export ", STDERR_FILENO);
		ft_putstr_fd("[-fn] [name[=value] ...] or export -p\n", STDERR_FILENO);
		g_exit_status = 2;
		return (envp);
	}
	while (args[++i] && !g_exit_status)
		envp = cmd_export_loop(args[i], envp);
	return (envp);
}
