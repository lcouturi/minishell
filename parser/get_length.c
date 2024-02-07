/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/17 22:20:27 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	getsize(long n)
{
	int	s;

	s = 1;
	if (!n)
		s++;
	while (n && s++)
		n /= 10;
	return (s);
}

static int	handle_envvar(char *str, char **envp, int *i)
{
	if (str[++i[0]] == '?')
	{
		i[5] += getsize(exit_status / 256);
		return (1);
	}
	i[1] = i[0];
	while (ft_isalnum(str[i[1]]))
		i[1]++;
	i[2] = 0;
	while (envp[i[2]] && (ft_strncmp(envp[i[2]], str + i[0], i[1] - i[0])
			|| envp[i[2]][i[1] - i[0]] != '='))
		i[2]++;
	if (envp[i[2]])
		i[5] += ft_strlen(envp[i[2]]) - (i[1] - i[0] + 1);
	i[0] = i[1] - 1;
	return (0);
}

void	get_length(char *str, char **envp, int *i)
{
	quote_check(str, i);
	if (!i[4] && str[i[0]] == '$' && handle_envvar(str, envp, i))
		return ;
	else if (i[0] && !i[3] && !i[4] && isop(str[i[0]]) && !isop(str[i[0] - 1]))
	{
		i[5] += 2;
		if (str[i[0] + 1] && !isop(str[i[0] + 1]))
			i[5] += 1;
	}
	else if (!i[3] && !i[4] && isop(str[i[0]]) && str[i[0] + 1]
		&& !isop(str[i[0] + 1]))
		i[5] += 2;
	else
		i[5]++;
}
