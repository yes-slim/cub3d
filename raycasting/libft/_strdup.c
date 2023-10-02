/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:07:24 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/28 15:34:27 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*_strdup(const char *src)
{
	size_t	i;
	size_t	len;
	char	*dup;

	i = 0;
	len = _strlen(src);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
