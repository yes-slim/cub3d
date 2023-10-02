/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:21:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:57 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlcpy(char *dest, char *src, int dstsize)
{
	int	i;
	int	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
		return (src_size);
	dest[i] = '\0';
	return (src_size);
}

char	*ft_strdup(char *s1)
{
	int		size;
	char	*s;

	size = ft_strlen(s1) + 1;
	s = (char *)malloc(sizeof(char) * size);
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, size);
	return (s);
}

char	*ft_strjoin(char *s1, char *s2, int len)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	result = malloc (sizeof(char) * (len + 1));
	if (!result)
		exit(errno);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	if (s1)
		free(s1);
	return (result);
}
