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
	if (strarrlen(args) > 2)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (args[1] && ft_strncmp(args[1], "-", 2) && chdir(args[1]) == -1)
	{
		g_exit_status = EXIT_FAILURE;
		errno = ENOENT;
		ft_putstr_fd("minshell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(0);
		return (1);
	}
	return (0);
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

void	cmd_cd(char **args, char **envp)
{
	char	*cwd;

	if (error_check(args))
		return ;
	g_exit_status = EXIT_SUCCESS;
	if (!ft_strncmp(args[1], "-", 2))
	{
		chdir(ft_getenv("OLDPWD", envp));
		printf("%s\n", ft_getenv("OLDPWD", envp));
	}
	else if (!args[1])
		chdir(ft_getenv("HOME", envp));
	ft_setenv("OLDPWD", ft_getenv("PWD", envp), envp);
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, envp);
	free(cwd);
}
