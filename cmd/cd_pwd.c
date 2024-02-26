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

static char	*newpwd_loop(char **mod, t_node *node, int i)
{
	char	*tmp;

	if (!ft_strncmp(mod[i], ".", 2))
		return (node->pwd);
	else if (!ft_strncmp(mod[i], "..", 3))
		tmp = ft_substr(node->pwd, 0, ft_strrchr(node->pwd, '/') - node->pwd);
	else
	{
		if (ft_strncmp(node->pwd, "/", 2))
		{
			tmp = ft_strjoin(node->pwd, "/");
			free(node->pwd);
			node->pwd = tmp;
		}
		tmp = ft_strjoin(node->pwd, mod[i]);
	}
	free(node->pwd);
	node->pwd = tmp;
	return (node->pwd);
}

char	*newpwd(t_node *node, char *cmd)
{
	int		i;
	char	**mod;

	i = -1;
	mod = ft_split(cmd, '/');
	if (cmd[0] == '/')
	{
		free(node->pwd);
		node->pwd = ft_strdup("/");
	}
	while (mod[++i])
		node->pwd = newpwd_loop(mod, node, i);
	strarrfree(mod);
	if (!node->pwd[0])
	{
		free(node->pwd);
		node->pwd = ft_strdup("/");
	}
	return (node->pwd);
}
