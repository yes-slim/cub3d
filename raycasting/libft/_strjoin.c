/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:55:25 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/28 15:34:12 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*new;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		return (_strdup(s2));
	i = 0;
	j = _strlen(s1);
	new = malloc(_strlen(s1) + _strlen(s2) * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}
