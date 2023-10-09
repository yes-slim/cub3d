/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:26:07 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/09 02:26:10 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	pars_fc_value(char *arg, int i, int *conver, int *result)
{
	int	value;

	value = convert_rgb(&arg[i], *conver);
	if (value == -1)
		return (-1);
	*result += value;
	*conver -= 8;
	return (VALID);
}

int	check_space_comp(t_data *data)
{
	t_coordinate	p;
	int				flag;

	p.y = 0;
	flag = 0;
	while (data->mp[p.y])
	{
		p.x = 0;
		while (data->mp[p.y][p.x])
		{
			if (is_space(data->mp[p.y][p.x]) && !valid_space(data, p.x, p.y))
				return (ERROR);
			if (data->mp[p.y][p.x] == '0' && !check_position(data, p.y, p.x))
				return (ERROR);
			else if (data->mp[p.y][p.x] == 'N' || data->mp[p.y][p.x] == 'S'
				|| data->mp[p.y][p.x] == 'E' || data->mp[p.y][p.x] == 'W')
				if (set_player_info(data, p, &flag) == ERROR)
					return (ERROR);
			p.x++;
		}
		p.y++;
	}
	if (!flag)
		return (ERROR);
	return (VALID);
}

int	set_player_info(t_data *data, t_coordinate p, int *flag)
{
	if (*flag)
		return (ERROR);
	*flag = 1;
	if (check_position(data, p.y, p.x) == ERROR)
		return (ERROR);
	data->x = (double)(p.x * CELL) + ((double)CELL / 2);
	data->y = (double)(p.y * CELL) + ((double)CELL / 2);
	direc_angle(data, data->mp[p.y][p.x]);
	data->mp[p.y][p.x] = '0';
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
	return (VALID);
}
