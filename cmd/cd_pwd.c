/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 23:35:20 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*newpwd_loop(char **mod, char *pwd, int i)
{
	char	*tmp;

	if (!ft_strncmp(mod[i], ".", 2))
		return (pwd);
	else if (!ft_strncmp(mod[i], "..", 3))
		tmp = ft_substr(pwd, 0, ft_strrchr(pwd, '/') - pwd);
	else
	{
		if (ft_strncmp(pwd, "/", 2))
		{
			tmp = ft_strjoin(pwd, "/");
			free(pwd);
			pwd = tmp;
		}
		tmp = ft_strjoin(pwd, mod[i]);
	}
	free(pwd);
	pwd = tmp;
	return (pwd);
}

char	*newpwd(char *pwd, char *cmd)
{
	int		i;
	char	**mod;

	i = -1;
	mod = ft_split(cmd, '/');
	if (cmd[0] == '/')
	{
		free(pwd);
		pwd = ft_strdup("/");
	}
	while (mod[++i])
		pwd = newpwd_loop(mod, pwd, i);
	strarrfree(mod);
	if (!pwd[0])
	{
		free(pwd);
		pwd = ft_strdup("/");
	}
	return (pwd);
}
