/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/27 09:21:21 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	backup_restor(t_node *node)
{
	dup2(node->backup_stdout, STDOUT_FILENO);
	dup2(node->backup_stdin, STDIN_FILENO);
}

char	**split_before_pipe_args(char **args, t_node *node)
{
	char	**temp;
	int		i;
	int		j;

	i = -1;
	temp = malloc((node->pipe_idx) * sizeof(char *));
	if (temp < 0)
		return (NULL);
	while (++i < node->pipe_idx - 1)
	{
		temp[i] = malloc(ft_strlen(args[i]));
		if (temp[i] < 0)
			return (NULL);
		j = 0;
		while (args[i][j])
		{
			temp[i][j] = args[i][j];
			j++;
		}
		temp[i][j] = '\0';
	}
	temp[++i] = NULL;
	return (temp);
}
