/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/17 22:20:27 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_length_loop(char *str, char **envp, int *i)
{
	quote_check(str, i);
	if (!i[4] && str[i[0]] == '$')
	{
		i[0]++;
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
	}
	else
		i[5]++;
}

static int	get_length(char *str, char **envp)
{
	int		i[6];

	i[0] = -1;
	i[3] = 0;
	i[4] = 0;
	i[5] = 0;
	while (str[++i[0]])
		get_length_loop(str, envp, i);
	return (i[5] + 1);
}

static void	expand_envvar_loop(char *str, char *str2, char **envp, int *i)
{
	quote_check(str, i);
	if (!i[4] && str[i[0]] == '$')
	{
		i[0]++;
		i[5] = i[0];
		while (ft_isalnum(str[i[5]]))
			i[5]++;
		i[2] = 0;
		while (envp[i[2]] && (ft_strncmp(envp[i[2]], str + i[0], i[5] - i[0])
				|| envp[i[2]][i[5] - i[0]] != '='))
			i[2]++;
		if (envp[i[2]])
		{
			i[6] = i[5] - i[0] + 1;
			while (envp[i[2]][i[6]])
				str2[i[1]++] = envp[i[2]][i[6]++];
		}
		i[0] = i[5];
	}
	else
		str2[i[1]++] = str[i[0]++];
}

char	*expand_envvar(char *str, char **envp)
{
	int		i[7];
	char	*str2;

	i[0] = 0;
	i[1] = 0;
	i[3] = 0;
	i[4] = 0;
	str2 = malloc(get_length(str, envp));
	while (str[i[0]])
		expand_envvar_loop(str, str2, envp, i);
	str2[i[1]] = '\0';
	return (str2);
}
