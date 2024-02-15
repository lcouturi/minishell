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

static void	insert_int(t_args *args, int *i)
{
	int	j;

	j = 1000000000;
	while (j)
	{
		if (g_exit_status / j)
		{
			args->s[i[1]] = g_exit_status / j % 10 + '0';
			args->e[i[1]++] = false;
		}
		j /= 10;
	}
	if (!g_exit_status)
	{
		args->s[i[1]] = '0';
		args->e[i[1]++] = false;
	}
	i[0]++;
}

static void	no_env(int *i, t_args *args, t_args *args2)
{
	if (i[0] && !args->e[i[0]] && isop(args, i[0]) && !isop(args, i[0] - 1))
	{
		args2->s[i[1]] = ' ';
		args2->e[i[1]++] = false;
		args2->s[i[1]] = args->s[i[0]];
		args2->e[i[1]++] = args->e[i[0]++];
		if (args->s[i[0]] && !isop(args, i[0]))
		{
			args2->s[i[1]] = ' ';
			args2->e[i[1]] = false;
		}
	}
	else if (!args->e[i[0]] && isop(args, i[0]) && args->s[i[0] + 1]
		&& !isop(args, i[0] + 1))
	{
		args2->s[i[1]] = args->s[i[0]];
		args2->e[i[1]++] = args->e[i[0]++];
		args2->s[i[1]] = ' ';
		args2->e[i[1]++] = false;
	}
	else
	{
		args2->s[i[1]] = args->s[i[0]];
		args2->e[i[1]++] = args->e[i[0]++];
	}
}

static void	handle_envvar(int *i, t_args *args, t_args *args2, char **envp)
{
	i[5] = i[0];
	while (ft_isenv(args, i[5]))
		i[5]++;
	i[2] = 0;
	while (envp[i[2]] && (ft_strncmp(envp[i[2]], args->s + i[0], i[5] - i[0])
			|| envp[i[2]][i[5] - i[0]] != '='))
		i[2]++;
	if (envp[i[2]])
	{
		i[6] = i[5] - i[0] + 1;
		while (envp[i[2]][i[6]])
		{
			args2->s[i[1]] = envp[i[2]][i[6]++];
			args2->e[i[1]++] = false;
		}
	}
	i[0] = i[5];
}

static void	expand_envvar_loop(t_args *args, t_args *args2, char **envp)
{
	int	i[7];

	i[0] = 0;
	i[1] = 0;
	while (args->s[i[0]])
	{
		if (!args->e[i[0]] && args->s[i[0]] == '$' && ft_isenv(args, i[0] + 1))
		{
			if (args->s[++i[0]] == '?')
			{
				insert_int(args2, i);
				continue ;
			}
			handle_envvar(i, args, args2, envp);
		}
		else
			no_env(i, args, args2);
	}
	args2->s[i[1]] = '\0';
}

t_args	*expand_envvar(t_args *args, char **envp)
{
	int				i[6];
	static t_args	args2;

	i[0] = -1;
	i[5] = 0;
	while (args->s[++i[0]])
		get_length(args, envp, i);
	args2.s = malloc((i[5] + 1) * sizeof(char));
	args2.e = malloc((i[5]) * sizeof(bool));
	if (!args2.s || !args2.e)
	{
		free(args->s);
		free(args->e);
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	expand_envvar_loop(args, &args2, envp);
	printf("%s\n", args2.s);
	return (&args2);
}
