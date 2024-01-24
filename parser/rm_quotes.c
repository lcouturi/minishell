/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/24 00:40:30 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*rm_quotes_loop(char *str)
{
	int		i[5];
	int		j;
	int		l;
	char	*newstr;

	i[0] = -1;
	j = 0;
	l = 0;
	while (str[++i[0]])
	{
		quote_check(str, i);
		if (!(!i[4] && str[i[0]] == '\"') && !(!i[3] && str[i[0]] == '\''))
			l++;
	}
	newstr = malloc((l + 1) * sizeof(char));
	i[0] = -1;
	while (str[++i[0]])
	{
		quote_check(str, i);
		if (!(!i[4] && str[i[0]] == '\"') && !(!i[3] && str[i[0]] == '\''))
			newstr[j++] = str[i[0]];
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	**rm_quotes(char **args)
{
	int	j;

	j = -1;
	while (args[++j])
		args[j] = rm_quotes_loop(args[j]);
	return (args);
}
