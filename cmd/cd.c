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

static char	*ft_getenv(const char *name, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], name, ft_strlen(name))
		|| envp[i][ft_strlen(name)] != '=')
		i++;
	return (envp[i] + ft_strlen(name) + 1);
}

static int	ft_setenv(const char *name, const char *value, char **envp)
{
	int	i;
	int	n;

	i = 0;
	while (ft_strncmp(envp[i], name, ft_strlen(name))
		|| envp[i][ft_strlen(name)] != '=')
		i++;
	free(envp[i]);
	n = ft_strlen(name) + ft_strlen(value) + 2;
	envp[i] = malloc(n);
	if (!envp[i])
		return (1);
	ft_strlcpy(envp[i], name, n);
	ft_strlcat(envp[i], "=", n);
	ft_strlcat(envp[i], value, n);
	return (0);
}

void	cmd_cd(char **args, char **envp, t_node *node)
{
	int		i;
	char	*cwd;

	node->exit_status = EXIT_SUCCESS * 256;
	i = 0;
	if (args[1] && chdir(args[1]) == -1)
	{
		node->exit_status = EXIT_FAILURE * 256;
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
