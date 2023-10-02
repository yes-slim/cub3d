/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:36:30 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:57 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension_file(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (len < 4)
		return (ERROR);
	while (len && WHITESPACE(str[len]))
		len--;
	if (str[len] != 'b' || str[len - 1] != 'u'\
		|| str[len - 2] != 'c' || str[len - 3] != '.')
		return (ERROR);
	return (VALID);
}

int	check_map_edge(t_data *data, int y)
{
	int	x;

	x = 0;
	if (y == 0 || y + 1 == data->len_map)
	{
		while (data->mp[y][x])
		{
			if (data->mp[y][x] != ' ' && data->mp[y][x] != '1')
				return (ERROR);
			x++;
		}
	}
	else
	{
		while (WHITESPACE(data->mp[y][x]))
			x++;
		if (data->mp[y][x] != '1')
			return (ERROR);
		x = ft_strlen(data->mp[y]) - 1;
		while (WHITESPACE(data->mp[y][x]))
			x--;
		if (data->mp[y][x] != '1')
			return (ERROR);
	}
	return (VALID);
}

int	check_position(t_data *data, int y, int x)
{
	if (x == 0 || (x - 1 >= 0 && (!data->mp[y][x - 1] \
		|| WHITESPACE(data->mp[y][x - 1]))))
		return (ERROR);
	if (y == 0 || (y - 1 >= 0 && (!data->mp[y - 1][x] \
		|| WHITESPACE(data->mp[y - 1][x]))))
		return (ERROR);
	if (x + 1 >= ft_strlen(data->mp[y]) || (!data->mp[y][x + 1] \
		|| WHITESPACE(data->mp[y][x + 1])))
		return (ERROR);
	if (y + 1 >= data->len_map || (!data->mp[y + 1][x] \
		|| WHITESPACE(data->mp[y + 1][x])))
		return (ERROR);
	return (VALID);
}

int	check_space_comp(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->mp[y])
	{
		x = 0;
		while (data->mp[y][x])
		{
			if (WHITESPACE(data->mp[y][x]) && !valid_space(data, x, y))
				return (ERROR);
			if (data->mp[y][x] == '0' && check_position(data, y, x) == ERROR)
				return (ERROR);
			x++;
		}
		y++;
	}
	return (VALID);
}

int	check_map(t_data *data, int len, int j)
{
	t_map	*tmp;
	int		i;

	tmp = data->map;
	data->len_map = len;
	if (!data->map || data->len_map == 0)
		return (ERROR);
	data->mp = malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		i = 0;
		while (tmp->row[i] && tmp->row[i] != '\n')
		{
			if (map_component(tmp->row[i]) == ERROR)
				return (ERROR);
			i++;
		}
		tmp->row[i] = '\0';
		data->mp[j] = ft_strdup(tmp->row);
		tmp = tmp->next;
		j++;
		data->mp[j] = NULL;
	}
	return (check_space_comp(data));
}
