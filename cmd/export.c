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

static int	failure(char **args, t_node *node, int i)
{
	if (!args[1][0] || (!ft_isalnum(args[1][i]) && args[1][i] != '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", args[1]);
		node->exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

char	**cmd_export(char **args, char **envp, t_node *node)
{
	int	i;
	int	i2;

	i2 = 0;
	i = -1;
	if (!args[1])
		return (envp);
	while (args[1][++i] != '=')
	{
		if (i && !args[1][i])
			return (envp);
		else if (failure(args, node, i))
			return (envp);
	}
	while (ft_strncmp(envp[i2], args[1], i + 1))
		i2++;
	if (!envp[i2])
		strarradd(envp, args[1]);
	free(envp[i2]);
	envp[i2] = ft_strdup(args[1]);
	if (!envp[i2])
		exit(EXIT_FAILURE);
	node->exit_status = EXIT_SUCCESS;
	return (envp);
}
