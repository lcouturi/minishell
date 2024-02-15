/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/17 18:12:44 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isop(t_args *args, int i)
{
	return ((!args->e[i] && (args->s[i] == '<' || args->s[i] == '>'
				|| args->s[i] == '|')));
}

int	ft_isenv(t_args *args, int i)
{
	return ((!args->e[i] && (ft_isalnum(args->s[i]) || args->s[i] == '_'
				|| args->s[i] == '?')));
}
