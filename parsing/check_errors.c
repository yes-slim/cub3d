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

int	convert_listmap(t_data *data, int j)
{
	int		i;
	t_map	*tmp;

	tmp = data->map;
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
	return (VALID);
}

int	check_map(t_data *data, int len, int j)
{
	data->len_map = len;
	if (!data->map || data->len_map == 0)
		return (ERROR);
	data->mp = malloc(sizeof(char *) * (len + 1));
	if (!data->mp)
		return (ERROR);
	data->mp[0] = 0x00;
	if (convert_listmap(data, j) == ERROR)
		return (ERROR);
	trim_spaces(data);
	map_padding(data);
	return (check_space_comp(data));
}
