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
		return (1);
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
	else if (!strarradd(envp, str))
		return (1);
	return (0);
}

void	cmd_cd(char **args, char **envp)
{
	int		i;
	char	*cwd;

	exit_status = EXIT_SUCCESS;
	i = 0;
	if (args[1] && chdir(args[1]) == -1)
	{
		exit_status = EXIT_FAILURE;
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
		return ;
	}
	else if (!args[1])
	{
		while (ft_strncmp(envp[i], "HOME=", 5))
			i++;
		chdir(envp[i] + 5);
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", envp), envp);
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, envp);
	free(cwd);
}
