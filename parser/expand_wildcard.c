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

// THE PLAN:
// 1.	Use opendir and readdir to get the names of all files in the current
//		working directory and create a linked list from it. Exclude all files
//		which start with a period.
// 2.	Turn the linked list into ASCII-ordered string array.
// 3.	For every argument in the command with a non-quoted asterisk, replace
//		the argument with every file in the linked list which matches the
//		wildcard, surounding each with single quotes to account for the
//		potential use of special characters in file names. ASCII order must be
//		maintained. For instance, ls expand_*.c turns into ls 'expand_envvar.c'
//		'expand_wildcard.c'. If no matching files are found, the argument is
//		left as-is.

static char	*lowest(t_list *lst)
{
	char	*ret;
	t_list	*tmp;
	t_list	*tmplow;

	tmplow = lst;
	while (!tmplow->content)
		tmplow = tmplow->next;
	tmp = tmplow->next;
	while (tmp)
	{
		if (ft_strncmp(tmplow->content, tmp->content, ft_strlen(tmplow->content)) > 0)
			tmplow = tmp;
		tmp = tmp->next;
	}
	ret = ft_strdup(tmplow->content);
	free(tmplow->content);
	tmplow->content = 0;
	return (ret);
}

void	expand_wildcard(void)
{
	DIR*			dir;
	struct dirent*	dr;
	char			**files;
	int				i;
	t_list			*lst;

	dir = opendir(".");
	dr = readdir(dir);
	if (dr->d_name[0] != '.')
		lst = ft_lstnew(dr->d_name);
	while ((dr = readdir(dir)))
		if (dr->d_name[0] != '.')
			ft_lstadd_back(&lst, ft_lstnew(dr->d_name));
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
	closedir(dir);
	free_string_array(files);
}
