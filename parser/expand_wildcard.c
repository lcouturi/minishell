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

static char	**get_file_list(void)
{
	DIR				*dir;
	struct dirent	*dr;
	char			**files;
	int				i;
	t_list			*lst;

	dir = opendir(".");
	dr = readdir(dir);
	while (dr && dr->d_name[0] == '.')
		dr = readdir(dir);
	if (!dr)
	{
		closedir(dir);
		return (0);
	}
	lst = ft_lstnew(ft_strdup(dr->d_name));
	while (1)
	{
		dr = readdir(dir);
		if (!dr)
			break ;
		if (dr->d_name[0] != '.')
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
	closedir(dir);
	return (files);
}

void	match(char *str, char **files, int *i)
{
	char	**split;

	split = ft_split(str + i[5], '*');
	if (str[i[5]] != '*')
	{
		printf("%s, %s\n", split[0], files[i[1]]);
		if (ft_strncmp(split[0], files[i[1]], ft_strlen(split[0])))
		{
			free_string_array(split);
			files[i[1]][0] = '\0';
			return ;
		}
	}
}

char	*expand_wildcard(char *str)
{
	char	**files;
	int		i[7];

	i[0] = 0;
	i[3] = 0;
	i[4] = 0;
	while (str[i[0]])
	{
		quote_check(str, i);
		if (!i[3] && !i[4] && str[i[0]] == '*')
		{
			files = get_file_list();
			while (!ft_isspace(str[i[0]]))
				i[0]--;
			i[0]++;
			i[1] = -1;
			while (files[++i[1]])
			{
				i[5] = i[0];
				i[2] = 0;
				match(str, files, i);
			}
			i[1] = -1;
			while (files[++i[1]])
				if (files[i[1]][0])
					printf("%s\n", files[i[1]]);
			free_string_array(files);
			while (str[i[0]] && !ft_isspace(str[i[0]]))
				i[0]++;
		}
		else
			i[0]++;
	}
	return (str);
}
