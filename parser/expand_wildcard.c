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

static void	get_arg_num_loop(char **args, int *i, int *n)
{
	char	**files;
	int		n2;
	char	**split;

	files = get_file_list(args[i[2]][0] == '.');
	i[1] = -1;
	split = asterisk_splitter(args[i[2]]);
	split = rm_quotes(split);
	while (files[++i[1]])
		match(args[i[2]], split, files, i[1]);
	strarrfree(split);
	i[1] = -1;
	n2 = 0;
	while (files[++i[1]])
		if (files[i[1]][0])
			n2++;
	if (!n2)
		*n += 1;
	else
		*n += n2;
	strarrfree(files);
}

static int	get_arg_num(char **args)
{
	int	i[5];
	int	n;

	i[2] = -1;
	n = 0;
	while (args[++i[2]])
	{
		i[0] = -1;
		while (args[i[2]][++i[0]])
		{
			quote_check(args[i[2]], i);
			if (!i[3] && !i[4] && args[i[2]][i[0]] == '*')
			{
				get_arg_num_loop(args, i, &n);
				break ;
			}
		}
	}
	return (n);
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
		i[5] += 1;
	}
}

static void	wildcard_handler(char **args, char **newargs, int *i)
{
	char	**files;
	char	**split;

	files = get_file_list(args[i[2]][0] == '.');
	i[1] = -1;
	split = asterisk_splitter(args[i[2]]);
	split = rm_quotes(split);
	while (files[++i[1]])
		match(args[i[2]], split, files, i[1]);
	strarrfree(split);
	i[1] = -1;
	wildcard_loop(files, i, newargs, args);
	strarrfree(files);
}

char	**expand_wildcard(char **args)
{
	int		i[6];
	char	**newargs;

	newargs = malloc((strarrlen(args) + get_arg_num(args) + 1) * 8);
	i[2] = -1;
	i[5] = 0;
	while (args[++i[2]])
	{
		i[0] = -1;
		while (args[i[2]][++i[0]])
		{
			quote_check(args[i[2]], i);
			if (!i[3] && !i[4] && args[i[2]][i[0]] == '*')
			{
				wildcard_handler(args, newargs, i);
				break ;
			}
		}
		if (!args[i[2]][i[0]])
			newargs[i[5]++] = ft_strdup(args[i[2]]);
	}
	strarrfree(args);
	newargs[i[5]] = 0;
	return (newargs);
}
