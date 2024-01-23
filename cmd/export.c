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

static void	cmd_export_add(char **args, char **envp, int i)
{
	static int	hack = 1;
	int			i2;

	i2 = 0;
	while (ft_strncmp(envp[i2], args[1], i + 1))
		i2++;
	if (!envp[i2])
	{
		strarradd(envp, args[1]);
		if (hack)
		{
			strarradd(envp, args[1]);
			hack = 0;
		}
		return ;
	}
	free(envp[i2]);
	envp[i2] = ft_strdup(args[1]);
}

void	cmd_export(char **args, char **envp)
{
	int	i;

	i = -1;
	if (!args[1])
		return ;
	while (args[1][++i] != '=')
	{
		if (i && !args[1][i])
			return ;
		else if (!args[1][0] || (!ft_isalnum(args[1][i]) && args[1][i] != '_'))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				args[1]);
			return ;
		}
	}
	cmd_export_add(args, envp, i);
}
