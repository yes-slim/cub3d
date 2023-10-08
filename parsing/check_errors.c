/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:36:30 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/08 23:15:58 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		while (is_space(data->mp[y][x]))
			x++;
		if (data->mp[y][x] != '1')
			return (ERROR);
		x = ft_strlen(data->mp[y]) - 1;
		while (is_space(data->mp[y][x]))
			x--;
		if (data->mp[y][x] != '1')
			return (ERROR);
	}
	return (VALID);
}

int	check_position(t_data *data, int y, int x)
{
	if (!x || !y || x == ft_strlen(data->mp[y]) - 1 \
		|| y == data->len_map - 1)
		return (ERROR);
	if (x + 1 > ft_strlen(data->mp[y])
		|| !data->mp[y][x + 1] || is_space(data->mp[y][x + 1]))
		return (ERROR);
	if (x - 1 < 0 || is_space(data->mp[y][x - 1]))
		return (ERROR);
	if (y + 1 >= data->len_map || x > ft_strlen(data->mp[y + 1])
		|| !data->mp[y + 1][x] || is_space(data->mp[y + 1][x]))
		return (ERROR);
	if (x > ft_strlen(data->mp[y - 1]) || !data->mp[y - 1][x]
		|| is_space(data->mp[y - 1][x]))
		return (ERROR);
	/*if (x == 0 || (x - 1 >= 0 && (!data->mp[y][x - 1]
		|| is_space(data->mp[y][x - 1]))))
		return (ERROR);
	if (y == 0 || (y - 1 >= 0 && (ft_strlen(data->mp[y - 1]) < x || !data->mp[y - 1][x]
		|| is_space(data->mp[y - 1][x]))))
		return (ERROR);
	if (x + 1 >= ft_strlen(data->mp[y]) || (!data->mp[y][x + 1]
		|| is_space(data->mp[y][x + 1])))
		return (ERROR);
	if (y + 1 >= data->len_map || ft_strlen(data->mp[y + 1]) < x
		|| !data->mp[y + 1][x] || is_space(data->mp[y + 1][x]))
		return (ERROR);*/
	return (VALID);
}

void	direc_angle(t_data *data, char symbol)
{
	if (symbol == 'N')
		data->angel = get_rad(90);
	if (symbol == 'E')
		data->angel = get_rad(0);
	if (symbol == 'W')
		data->angel = get_rad(180);
	if (symbol == 'S')
		data->angel = get_rad(270);
}

int	check_space_comp(t_data *data)
{
	int	x;
	int	flag;
	int	y;

	y = 0;
	flag = 0;
	while (data->mp[y])
	{
		x = 0;
		while (data->mp[y][x])
		{
			if (is_space(data->mp[y][x]) && !valid_space(data, x, y))
			{
				return (ERROR);
			}
			if (data->mp[y][x] == '0' && check_position(data, y, x) == ERROR)
				return (ERROR);
			else if (data->mp[y][x] == 'N' || data->mp[y][x] == 'S'
				|| data->mp[y][x] == 'E' || data->mp[y][x] == 'W')
			{
				if (flag)
					return (ERROR);
				flag = 1;
				if (check_position(data, y, x) == ERROR)
					return (ERROR);
				data->x = (double)(x * CELL) + ((double)CELL / 2);
				data->y = (double)(y * CELL) + ((double)CELL / 2);
				direc_angle(data, data->mp[y][x]);
				data->mp[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (!flag)
	{
		return (ERROR);
	}
	return (VALID);
}

void	map_padding(t_data *data)
{
	char	*new;
	int		y;
	int		x;

	y = 0;
	while (data->mp[y])
	{
		if (ft_strlen(data->mp[y]) < data->map_w)
		{
			new = malloc(sizeof(char) * (data->map_w + 1));
			ft_strlcpy(new, data->mp[y], data->map_w + 1);
			x = ft_strlen(data->mp[y]);
			while (x < data->map_w)
			{
				new[x] = ' ';
				x++;
			}
			new[x] = '\0';
			free(data->mp[y]);
			data->mp[y] = new;
		}
		y++;
	}
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
	data->mp[0] = 0x00;
	while (tmp)
	{
		i = 0;
		while (tmp->row[i] && tmp->row[i] != '\n')
		{
			if (map_component(tmp->row[i]) == ERROR)
				return (ERROR);
			i++;
		}
		if (i)
			tmp->row[i] = '\0';
		if (i > data->map_w)
			data->map_w = i;
		data->mp[j] = ft_strdup(tmp->row);
		tmp = tmp->next;
		j++;
		data->mp[j] = NULL;
	}
	trim_spaces(data);
	map_padding(data);
	return (check_space_comp(data));
}
