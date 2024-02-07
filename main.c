/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:27:22 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;
	t_node	node;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	envp_copy = strarrcpy(envp);
	set_signal();
	while (1)
	{
		line = readline("minishell$ ");
		init_node(&node);
		if (line)
		{
			if (ft_strncmp(line, "\0", 1))
				envp_copy = parser(line, envp_copy, &node);
		}
		else
			cmd_exit_no_arg();
	}
	return (0);
}
