/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:34:53 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:57 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	valid_space(t_data *data, int x, int y)
{
	int	rowlen;

	rowlen = ft_strlen(data->mp[y]);
	if (x + 1 < rowlen && (!WHITESPACE(data->mp[y][x + 1]) \
			&& data->mp[y][x + 1] != '1'))
		return (ERROR);
	if (y + 1 < data->len_map && (!WHITESPACE(data->mp[y + 1][x]) \
			&& data->mp[y + 1][x] != '1'))
		return (ERROR);
	if (x - 1 >= 0 && (!WHITESPACE(data->mp[y][x - 1]) \
			&& data->mp[y][x - 1] != '1'))
		return (ERROR);
	if (y - 1 >= 0 && (!WHITESPACE(data->mp[y - 1][x]) \
			&& data->mp[y - 1][x] != '1'))
		return (ERROR);
	return (VALID);
}

int	map_component(char c)
{
	char	*elem;
	int		i;

	i = 0;
	elem = "01NSEW";
	if (WHITESPACE(c))
		return (VALID);
	while (elem[i])
		if (elem[i++] == c)
			return (VALID);
	return (ERROR);
}
