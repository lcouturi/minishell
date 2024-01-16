/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 18:17:38 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void handler(int signum)
{
	if (signum != SIGINT)
		return;
	printf("ctrl + c\n");
	rl_on_new_line();
	//rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	int ret;
	char *line;

	ret = 1;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("input> ");
		if (line)
		{
			if (ret)
				printf("output> %s\n", line);
			add_history(line);
			free(line);
			line = NULL;
		}
		else
		{
			printf("ctrl + d\n");
		}
	}
	return (0);
}
