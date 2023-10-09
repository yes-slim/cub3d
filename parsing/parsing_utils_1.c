/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:55:49 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/06 01:50:12 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	inside_circle(int x, int y)
{
	int	distance;

	distance = sqrt((x - M_CEN_X) * (x - M_CEN_X) \
				+ (y - M_CEN_Y) * (y - M_CEN_Y));
	return (distance <= MINI_RAD);
}

void	trim_spaces(t_data *data)
{
	int	y;
	int	x;

	y = data->len_map - 1;
	data->map_h = data->len_map;
	while (y && data->mp[y])
	{
		x = 0;
		while (data->mp[y][x])
		{
			if (!is_space(data->mp[y][x]))
				return ;
			x++;
		}
		free(data->mp[y]);
		data->mp[y] = NULL;
		data->map_h = y;
		y--;
	}
}
