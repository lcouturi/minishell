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

int	isop(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_isenv(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}
