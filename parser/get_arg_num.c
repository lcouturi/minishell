/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_num.c                                      :+:      :+:    :+:   */
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
	split = escape_split(args[i[2]], '*');
	split = rm_quotes_wildcards(split);
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

int	get_arg_num(char **args)
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
