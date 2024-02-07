/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarrutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 22:27:22 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	strarraddfree(char **strs, char *str)
{
	strarrfree(strs);
	free(str);
	exit(EXIT_FAILURE);
}

char	**strarradd(char **strs, char *str)
{
	int		i;
	char	**newstrs;

	i = 0;
	while (strs[i])
		i++;
	newstrs = malloc((i + 2) * 8);
	if (!newstrs)
		strarraddfree(strs, str);
	newstrs[i] = ft_strdup(str);
	if (!newstrs[i])
	{
		free(newstrs);
		strarraddfree(strs, str);
	}
	newstrs[i + 1] = 0;
	while (i--)
		newstrs[i] = strs[i];
	free(strs);
	return (newstrs);
}

char	**strarrcpy(char **strs)
{
	int		i;
	char	**newstrs;

	i = 0;
	while (strs[i])
		i++;
	newstrs = malloc((i + 1) * 8);
	if (!newstrs)
		exit(EXIT_FAILURE);
	i = -1;
	while (strs[++i])
	{
		newstrs[i] = ft_strdup(strs[i]);
		if (!newstrs[i])
		{
			strarrfree(newstrs);
			exit(EXIT_FAILURE);
		}
	}
	newstrs[i] = 0;
	return (newstrs);
}

void	strarrfree(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	strs = 0;
}

size_t	strarrlen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
