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

static void	insert_int(char *str, int *i)
{
	int	j;

	j = 1000000000;
	while (j)
	{
		if (g_exit_status / j)
			str[i[1]++] = g_exit_status / j % 10 + '0';
		j /= 10;
	}
	if (!g_exit_status)
		str[i[1]++] = '0';
	i[0] += 2;
}

static void	no_env(int *i, char *str, char *str2)
{
	if (i[0] && !i[3] && isop(str[i[0]]) && !isop(str[i[0] - 1]))
	{
		str2[i[1]++] = ' ';
		str2[i[1]++] = str[i[0]++];
		if (str[i[0]] && !isop(str[i[0]]))
			str2[i[1]++] = ' ';
	}
	else if (!i[3] && isop(str[i[0]]) && str[i[0] + 1] && !isop(str[i[0] + 1]))
	{
		str2[i[1]++] = str[i[0]++];
		str2[i[1]++] = ' ';
	}
	else
		str2[i[1]++] = str[i[0]++];
}

static void	handle_envvar(int *i, char *str, char *str2, char **envp)
{
	i[5] = ++i[0];
	while (ft_isenv(str[i[5]]))
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

static void	expand_envvar_loop(char *str, char *str2, char **envp)
{
	int	i[7];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		quote_check(str, i);
		if (i[3] < 2 && str[i[0]] == '$' && (ft_isenv(str[i[0] + 1])
				|| (i[3] != 1 && str[i[0] + 1] == '\"') || (i[3] < 2 && str[i[0]
						+ 1] == '\'')))
			handle_envvar(i, str, str2, envp);
		else if (i[3] < 2 && !ft_strncmp(str + i[0], "$?", 2))
			insert_int(str2, i);
		else
			no_env(i, str, str2);
	}
	str2[i[1]] = '\0';
}

char	*expand_envvar(char *str, char **envp)
{
	int		i[6];
	char	*str2;

	i[0] = -1;
	i[5] = 0;
	while (str[++i[0]])
		get_length(str, envp, i);
	str2 = malloc((i[5] + 1) * sizeof(char));
	if (!str2)
	{
		free(str);
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	expand_envvar_loop(str, str2, envp);
	return (str2);
}
