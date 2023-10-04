/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:55:49 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/05 00:20:51 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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