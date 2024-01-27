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
	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4))
		i++;
	free(envp[i]);
	cwd = getcwd(NULL, 0);
	envp[i] = ft_strjoin("PWD=", cwd);
	free(cwd);
}
