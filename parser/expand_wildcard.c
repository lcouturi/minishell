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

static void	match(char *str, char **split, char **files, int i)
{
	int		j;
	size_t	last;

	last = 0;
	j = -1;
	while (split[++j])
	{
		if (!ft_strnstr(files[i], split[j], ft_strlen(files[i]))
			|| (last > (size_t)ft_strnstr(files[i], split[j],
					ft_strlen(files[i]))))
		{
			files[i][0] = '\0';
			return ;
		}
		last = (size_t)ft_strnstr(files[i], split[j], ft_strlen(files[i]));
	}
	if ((str[0] != '*' && ft_strncmp(split[0], files[i], ft_strlen(split[0])))
		|| (str[ft_strlen(str) - 1] != '*' && ft_strncmp(split[j - 1], files[i]
				+ ft_strlen(files[i]) - ft_strlen(split[j - 1]),
				ft_strlen(split[j - 1]))))
	{
		files[i][0] = '\0';
		return ;
	}
}

char	**expand_wildcard(char **args)
{
	char	**files;
	int		i[5];
	char	**split;

	i[2] = -1;
	while (args[++i[2]])
	{
		i[0] = -1;
		while (args[i[2]][++i[0]])
		{
			quote_check(args[i[2]], i);
			if (!i[3] && !i[4] && args[i[2]][i[0]] == '*')
			{
				files = get_file_list();
				i[1] = -1;
				split = ft_split(args[i[2]], '*');
				while (files[++i[1]])
					match(args[i[2]], split, files, i[1]);
				strarrfree(split);
				cmd_env(files);
				strarrfree(files);
				break ;
			}
		}
	}
	return (args);
}
