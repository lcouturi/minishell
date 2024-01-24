/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:49:07 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_chk(char **args)
{
	size_t	str_len;
	int		i;

	i = -1;
	while (args[++i])
	{
		str_len = ft_strlen(args[i]);
		if (ft_strnstr(args[i], "<<", str_len)
			|| ft_strnstr(args[i], ">>", str_len)
			|| ft_strnstr(args[i], "<", str_len)
			|| ft_strnstr(args[i], ">", str_len))
			return (1);
	}
	return (0);
}
