/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:20:49 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/28 15:34:42 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define BUFFER_SIZE 10

size_t	_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	i = _strlen(str);
	if ((char)c == '\0')
		return ((char *)&str[i]);
	i = 0;
	while (str[i] != (char)c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	return ((char *)&str[i]);
}

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!_strchr(str, '\n') && i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free (str);
			free (buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = _strjoin(str, buffer);
	}
	free (buffer);
	return (str);
}

char	*ft_fill(char *str)
{
	char	*ret;
	int		i;
	int		z;

	i = 0;
	z = 0;
	if (!_strlen(str))
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	while (z < i && str[z])
	{
		ret[z] = str[z];
		z++;
	}
	ret[z] = '\0';
	return (ret);
}

char	*ft_remainder(char *str)
{
	char	*remainder;
	int		i;
	int		z;

	i = 0;
	z = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	remainder = malloc(sizeof(char) * (_strlen(str) - i + 1));
	if (!remainder)
	{
		free (str);
		return (NULL);
	}
	while (str[i])
		remainder[z++] = str[i++];
	remainder[z] = '\0';
	free (str);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*str[FOPEN_MAX];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE < 0 || fd > FOPEN_MAX)
		return (NULL);
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	ret = ft_fill(str[fd]);
	str[fd] = ft_remainder(str[fd]);
	return (ret);
}
