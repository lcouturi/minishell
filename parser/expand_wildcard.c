/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/20 20:01:00 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	failcheck(char **files, int *i, char **newargs, char **args)
{
	if (!newargs[i[5]])
	{
		strarrfree(newargs);
		strarrfree(args);
		strarrfree(files);
		exit(EXIT_FAILURE);
	}
}

static void	wildcard_loop(char **files, int *i, char **newargs, char **args)
{
	bool	flag;

	flag = 0;
	while (files[++i[1]])
	{
		if (files[i[1]][0])
		{
			newargs[i[5]] = malloc(ft_strlen(files[i[1]]) + 3);
			failcheck(files, i, newargs, args);
			ft_strlcpy(newargs[i[5]], "\'", ft_strlen(files[i[1]]) + 3);
			ft_strlcat(newargs[i[5]], files[i[1]], ft_strlen(files[i[1]]) + 3);
			ft_strlcat(newargs[i[5]], "\'", ft_strlen(files[i[1]]) + 3);
			i[5] += 1;
			flag = 1;
		}
	}
	if (!flag)
	{
		newargs[i[5]] = ft_strdup(args[i[2]]);
		failcheck(files, i, newargs, args);
		i[5] += 1;
	}
}

static void	wildcard_handler(char **args, char **newargs, int *i)
{
	char	**files;
	char	**split;

	files = get_file_list(args[i[2]][0] == '.');
	i[1] = -1;
	split = escape_split(ft_strdup(args[i[2]]), "*");
	split = rm_quotes_wildcards(split);
	while (files[++i[1]])
		match(args[i[2]], split, files, i[1]);
	strarrfree(split);
	i[1] = -1;
	wildcard_loop(files, i, newargs, args);
	strarrfree(files);
}

static void	expand_wildcard_loop(int *i, char **args, char **newargs,
	char **envp)
{
	i[0] = -1;
	tilde_handler(args, i, envp);
	while (args[i[2]][++i[0]])
	{
		quote_check(args[i[2]], i);
		if (!i[3] && args[i[2]][i[0]] == '*')
		{
			wildcard_handler(args, newargs, i);
			break ;
		}
	}
	if (!args[i[2]][i[0]])
	{
		newargs[i[5]++] = ft_strdup(args[i[2]]);
		if (!newargs[i[5] - 1])
		{
			strarrfree(newargs);
			strarrfree(args);
			exit(EXIT_FAILURE);
		}
	}
}

char	**expand_wildcard(char **args, char **envp)
{
	int		i[6];
	char	**newargs;

	newargs = malloc((strarrlen(args) + get_arg_num(args) + 1) * 8);
	if (!newargs)
	{
		strarrfree(args);
		exit(EXIT_FAILURE);
	}
	i[2] = -1;
	i[5] = 0;
	while (args[++i[2]])
		expand_wildcard_loop(i, args, newargs, envp);
	strarrfree(args);
	newargs[i[5]] = 0;
	return (newargs);
}
