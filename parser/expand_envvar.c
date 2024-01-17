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

static int	get_length(char *str, char **envp)
{
	int		i[5];
	int		l;
	char	*name;

	i[0] = -1;
	i[3] = 0;
	i[4] = 0;
	l = 0;
	while (str[++i[0]])
	{
		quote_check(str, i);
		if (!i[4] && str[i[0]] == '$')
		{
			i[1] = i[0] + 1;
			while (ft_isalnum(str[i[1]]))
				i[1]++;
			name = malloc((i[1] - i[0]) + 1 & sizeof(char));
			i[1] = 0;
			i[0]++;
			while (ft_isalnum(str[i[0]]))
				name[i[1]++] = str[i[0]++];
			name[i[1]++] = '=';
			name[i[1]] = '\0';
			i[2] = 0;
			while (envp[i[2]] && ft_strncmp(envp[i[2]], name, ft_strlen(name)))
				i[2]++;
			if (envp[i[2]])
				l += ft_strlen(envp[i[2]]) - ft_strlen(name);
			free(name);
			l += i[3] * 2;
		}
		else
			l++;
	}
	return (l);
}

char	*expand_envvar(char *str, char **envp)
{
	int		i[5];
	int		i2;
	char	*name;
	char	*str2;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	str2 = malloc(get_length(str, envp));
	while (str[i[0]])
	{
		quote_check(str, i);
		if (!i[4] && str[i[0]] == '$')
		{
			if (!i[3])
				str2[i[1]++] = '\"';
			i[2] = i[0] + 1;
			while (ft_isalnum(str[i[2]]))
				i[2]++;
			name = malloc(i[2] - i[0] + 1 & sizeof(char));
			i[2] = 0;
			i[0]++;
			while (ft_isalnum(str[i[0]]))
				name[i[2]++] = str[i[0]++];
			name[i[2]++] = '=';
			name[i[2]] = '\0';
			i[2] = 0;
			while (envp[i[2]] && ft_strncmp(envp[i[2]], name, ft_strlen(name)))
				i[2]++;
			if (envp[i[2]])
			{
				i2 = ft_strlen(name);
				while (envp[i[2]][i2])
					str2[i[1]++] = envp[i[2]][i2++];
			}
			if (!i[3])
				str2[i[1]++] = '\"';
			free(name);
		}
		else
			str2[i[1]++] = str[i[0]++];
	}
	str2[i[1]] = '\0';
	return (str2);
}
