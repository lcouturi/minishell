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

int	isop(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&');
}

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

static void	insert_int(char *str, int *i, t_node *node)
{
	int	j;

	j = 1000000000;
	while (j)
	{
		if (node->exit_status / 256 / j)
			str[i[1]++] = node->exit_status / 256 / j % 10 + '0';
		j /= 10;
	}
	if (!(node->exit_status / 256))
		str[i[1]++] = '0';
	i[0]++;
}

static void	get_length_loop(char *str, char **envp, int *i, t_node *node)
{
	quote_check(str, i);
	if (!i[4] && str[i[0]] == '$')
	{
		if (str[++i[0]] == '?')
		{
			i[5] += getsize(node->exit_status / 256);
			return ;
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
	}
	else if (i[0] && !i[3] && !i[4] && isop(str[i[0]]) && !isop(str[i[0] - 1]))
	{
		i[5] += 2;
		if (str[i[0] + 1] && !isop(str[i[0] + 1]))
			i[5] += 1;
	}
	else if (!i[3] && !i[4] && isop(str[i[0]]) && str[i[0] + 1] && !isop(str[i[0] + 1]))
		i[5] += 2;
	else
		i[5]++;
}

static void	expand_envvar_loop(char *str, char *str2, char **envp, t_node *node)
{
	int	i[7];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		quote_check(str, i);
		if (!i[4] && str[i[0]] == '$')
		{
			if (str[++i[0]] == '?')
			{
				insert_int(str2, i, node);
				return ;
			}
			i[5] = i[0];
			while (ft_isalnum(str[i[5]]) || str[i[5]] == '_')
				i[5]++;
			i[2] = 0;
			while (envp[i[2]] && (ft_strncmp(envp[i[2]], str + i[0], i[5]
						- i[0]) || envp[i[2]][i[5] - i[0]] != '='))
				i[2]++;
			if (envp[i[2]])
			{
				i[6] = i[5] - i[0] + 1;
				while (envp[i[2]][i[6]])
					str2[i[1]++] = envp[i[2]][i[6]++];
			}
			i[0] = i[5];
		}
		else if (i[0] && !i[3] && !i[4] && isop(str[i[0]]) && !isop(str[i[0] - 1]))
		{
			str2[i[1]++] = ' ';
			str2[i[1]++] = str[i[0]++];
			if (str[i[0]] && !isop(str[i[0]]))
				str2[i[1]++] = ' ';
		}
		else if (!i[3] && !i[4] && isop(str[i[0]]) && str[i[0] + 1] && !isop(str[i[0] + 1]))
		{
			str2[i[1]++] = str[i[0]++];
			str2[i[1]++] = ' ';
		}
		else
			str2[i[1]++] = str[i[0]++];
	}
	str2[i[1]] = '\0';
}

char	*expand_envvar(char *str, char **envp, t_node *node)
{
	int		i[6];
	char	*str2;

	i[0] = -1;
	i[5] = 0;
	while (str[++i[0]])
		get_length_loop(str, envp, i, node);
	str2 = malloc((i[5] + 1) * sizeof(char));
	expand_envvar_loop(str, str2, envp, node);
	return (str2);
}
