/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/29 19:12:11 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_args	*escape(char *str)
{
	static t_args	args;
	bool			dquote;
	int				i;
	unsigned int	j;
	bool			squote;

	dquote = false;
	squote = false;
	args.s = malloc(ft_strlen(str) * sizeof(char) + 1);
	args.e = malloc(ft_strlen(str) * sizeof(bool));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !dquote)
			squote = !squote;
		else if (str[i] == '\"' && !squote)
			dquote = !dquote;
		else if (str[i] == '\\' && !dquote && !squote)
		{
			args.s[j] = str[++i];
			args.e[j++] = true;
		}
		else
		{
			args.s[j] = str[i];
			if (dquote || squote)
			{
				if (dquote && str[i] == '$')
				{
					args.e[j++] = false;
					while (++i && (ft_isalpha(str[i]) || str[i] == '?'
							|| str[i] == '_'))
					{
						args.s[j] = str[i];
						args.e[j++] = false;
					}
					i--;
				}
				else
					args.e[j++] = true;
			}
			else
				args.e[j++] = false;
		}
	}
	args.s[j] = '\0';
	return (&args);
}
