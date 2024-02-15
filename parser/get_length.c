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

static int	handle_envvar(t_args *args, char **envp, int *i)
{
	if (args->s[++i[0]] == '?')
	{
		i[5] += getsize(g_exit_status / 256);
		return (1);
	}
	i[1] = i[0];
	while (ft_isenv(args, i[1]))
		i[1]++;
	i[2] = 0;
	while (envp[i[2]] && (ft_strncmp(envp[i[2]], args->s + i[0], i[1] - i[0])
			|| envp[i[2]][i[1] - i[0]] != '='))
		i[2]++;
	if (envp[i[2]])
		i[5] += ft_strlen(envp[i[2]]) - (i[1] - i[0] + 1);
	i[0] = i[1] - 1;
	return (0);
}

void	get_length(t_args *args, char **envp, int *i)
{
	if (!args->e[i[0]] && args->s[i[0]] == '$' && ft_isenv(args, i[0] + 1)
		&& handle_envvar(args, envp, i))
		return ;
	else if (i[0] && !args->e[i[0]] && isop(args, i[0]) && !isop(args, i[0]
			- 1))
	{
		i[5] += 2;
		if (args->s[i[0] + 1] && !isop(args, i[0] + 1))
			i[5] += 1;
	}
	else if (!i[3] && !i[4] && isop(args, i[0]) && args->s[i[0] + 1]
		&& !isop(args, i[0] + 1))
		i[5] += 2;
	else
		i[5]++;
}
