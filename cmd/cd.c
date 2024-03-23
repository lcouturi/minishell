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

static bool	error_check(char *arg)
{
	if (chdir(arg) == -1)
	{
		g_exit_status = EXIT_FAILURE;
		errno = ENOENT;
		ft_putstr_fd("minshell: cd: ", STDERR_FILENO);
		perror(arg);
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

char	**ft_setenv(const char *name, const char *value, char **envp)
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
		envp[i] = ft_strdup(str);
	}
	else
		envp = strarradd(envp, str);
	free(str);
	return (envp);
}

static int	checks(char **args, char **envp, t_node *node, bool offset)
{
	if (strarrlen(args) > 2 + offset)
	{
		g_exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (!args[1 + offset])
		chdir(ft_getenv("HOME", envp));
	else if (!ft_strncmp(args[1 + offset], "-", 2))
	{
		free(node->pwd);
		node->pwd = ft_strdup(ft_getenv("OLDPWD", envp));
		chdir(node->pwd);
		printf("%s\n", ft_getenv("OLDPWD", envp));
	}
	else if (error_check(args[1 + offset]))
		return (1);
	return (0);
}

char	**cmd_cd(char **args, char **envp, t_node *node)
{
	bool	offset;

	if (node->pipe_flag)
		return (envp);
	offset = 0;
	if (args[1] && !ft_strncmp(args[1], "--", 3))
		offset++;
	g_exit_status = EXIT_SUCCESS;
	if (checks(args, envp, node, offset))
		return (envp);
	if (!args[1 + offset])
	{
		free(node->pwd);
		node->pwd = ft_strdup(ft_getenv("HOME", envp));
	}
	else if (ft_strncmp(args[1 + offset], "-", 2))
		node->pwd = newpwd(node, args[1 + offset]);
	envp = ft_setenv("OLDPWD", ft_getenv("PWD", envp), envp);
	envp = ft_setenv("PWD", node->pwd, envp);
	return (envp);
}
