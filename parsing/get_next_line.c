/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:57 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/04 02:55:04 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_try2read(int fd, char *line, char *buf, int *len)
{
	int		getting;

	getting = 1;
	buf = malloc(sizeof(char) * 2);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	while (ft_strchr(buf, '\n') == 0 && getting > 0)
	{
		getting = read(fd, buf, 1);
		if (getting == -1)
		{
			if (line)
				free(line);
			free(buf);
			return (NULL);
		}
		if (getting == 0)
			break ;
		buf[getting] = '\0';
		*len += getting;
		line = ft_strjoin(line, buf, *len);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	int				len;
	char			*buf;

	buf = NULL;
	len = 0;
	line = NULL;
	line = ft_try2read(fd, line, buf, &len);
	return (line);
}
