/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/26 16:47:24 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_file_list(bool hidden)
{
	DIR				*dir;
	struct dirent	*dr;
	char			**files;

	dir = opendir(".");
	dr = readdir(dir);
	while (hidden && dr && (dr->d_name[0] != '.' || !ft_strncmp(dr->d_name, ".",
				2) || !ft_strncmp(dr->d_name, "..", 3)))
		dr = readdir(dir);
	while (!hidden && dr && dr->d_name[0] == '.')
		dr = readdir(dir);
	if (!dr)
	{
		closedir(dir);
		files = malloc(8);
		if (!files)
			exit(EXIT_FAILURE);
		files[0] = 0;
		return (files);
	}
	return (load_lst(dr, dir, hidden));
}

void	match(char *str, char **split, char **files, int i)
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
