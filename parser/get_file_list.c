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

static char	*lowest(t_list *lst)
{
	char	*ret;
	t_list	*tmp;
	t_list	*low;

	low = lst;
	while (!low->content)
		low = low->next;
	tmp = low->next;
	while (tmp)
	{
		if (ft_strncmp(low->content, tmp->content, ft_strlen(low->content)) > 0)
			low = tmp;
		tmp = tmp->next;
	}
	ret = low->content;
	low->content = 0;
	return (ret);
}

static char	**load_lst(struct dirent *dr, DIR *dir, bool hidden)
{
	char	**files;
	int		i;
	t_list	*lst;

	lst = ft_lstnew(ft_strdup(dr->d_name));
	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (!hidden && dr->d_name[0] != '.')
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(dr->d_name)));
		if (hidden && dr->d_name[0] == '.' && ft_strncmp(dr->d_name, ".", 2) && ft_strncmp(dr->d_name, "..", 3))
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(dr->d_name)));
	}
	files = malloc(8 * ft_lstsize(lst) + 1);
	i = -1;
	while (++i < ft_lstsize(lst))
		files[i] = lowest(lst);
	files[i] = 0;
	while (lst)
	{
		free(lst);
		lst = lst->next;
	}
	return (files);
}

char	**get_file_list(bool hidden)
{
	DIR				*dir;
	struct dirent	*dr;
	char			**files;

	dir = opendir(".");
	dr = readdir(dir);
	while (hidden && dr && (dr->d_name[0] != '.' || !ft_strncmp(dr->d_name, ".", 2) || !ft_strncmp(dr->d_name, "..", 3)))
		dr = readdir(dir);
	while (!hidden && dr && dr->d_name[0] == '.')
		dr = readdir(dir);
	if (!dr)
	{
		closedir(dir);
		return (0);
	}
	files = load_lst(dr, dir, hidden);
	closedir(dir);
	return (files);
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
