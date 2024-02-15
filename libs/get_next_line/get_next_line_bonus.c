/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2023/11/23 18:06:25 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_buf(char *buf, int fd)
{
	int		rd;
	char	*tbuf;

	rd = 1;
	tbuf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!tbuf)
		return (0);
	while (!gn_strchr(buf, '\n') && rd)
	{
		rd = read(fd, tbuf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			buf = 0;
			break ;
		}
		tbuf[rd] = '\0';
		buf = gn_strjoin(buf, tbuf);
	}
	free(tbuf);
	return (buf);
}

static char	*get_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf[i])
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = malloc(i + 2 * sizeof(char));
	line[i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = buf[i];
		i--;
	}
	return (line);
}

static char	*trim_buf(char *buf)
{
	int		i;
	char	*newbuf;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (0);
	}
	newbuf = gn_strdup(buf + i + 1);
	free(buf);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buf[MAX_FD + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (0);
	buf[fd] = get_buf(buf[fd], fd);
	if (!buf[fd])
		return (0);
	line = get_line(buf[fd]);
	buf[fd] = trim_buf(buf[fd]);
	return (line);
}
