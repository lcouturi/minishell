/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 23:35:20 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	error_check(char **args)
{
	if (chdir(args[1]) == -1)
	{
		g_exit_status = EXIT_FAILURE;
		errno = ENOENT;
		ft_putstr_fd("minshell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(0);
		return (true);
	}
	return (false);
}

char	*ft_getenv(const char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], name, ft_strlen(name))
			|| envp[i][ft_strlen(name)] != '='))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + ft_strlen(name) + 1);
}

int	ft_setenv(const char *name, const char *value, char **envp)
{
	int		i;
	int		n;
	char	*str;

	n = ft_strlen(name) + ft_strlen(value) + 2;
	str = malloc(n);
	if (!str)
		exit(EXIT_FAILURE);
	ft_strlcpy(str, name, n);
	ft_strlcat(str, "=", n);
	ft_strlcat(str, value, n);
	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], name, ft_strlen(name))
			|| envp[i][ft_strlen(name)] != '='))
		i++;
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = str;
	}
	else
		strarradd(envp, str);
	return (0);
}

void	cmd_cd(char **args, char **envp, char *str)
{
	g_exit_status = EXIT_SUCCESS;
	if (strarrlen(args) > 2)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	else if (!args[1])
		chdir(ft_getenv("HOME", envp));
	else if (!ft_strncmp(args[1], "-", 2))
	{
		str = ft_strdup(ft_getenv("OLDPWD", envp));
		chdir(str);
		printf("%s\n", ft_getenv("OLDPWD", envp));
	}
	else if (error_check(args))
		return ;
	ft_setenv("OLDPWD", ft_getenv("PWD", envp), envp);
	if (!args[1])
		str = ft_strdup(ft_getenv("HOME", envp));
	else if (ft_strncmp(args[1], "-", 2))
		str = newpwd(ft_strdup(ft_getenv("OLDPWD", envp)), args[1]);
	ft_setenv("PWD", str, envp);
	free(str);
}
