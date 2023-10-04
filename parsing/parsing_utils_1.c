/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:55:49 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/04 04:20:01 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	trim_spaces(t_data *data)
{
	int	y;
	int	x;
	int	flag;

	y = data->len_map - 1;
	flag = 0;
	while (y && data->mp[y])
	{
		x = 0;
		while (data->mp[y][x])
		{
			if (!WHITESPACE(data->mp[y][x]))
			{
				flag = 1;
				break ;
			}
			x++;
		}
		if (flag)
			return ;
		free(data->mp[y]);
		data->mp[y] = NULL;
		data->len_map--;
		y--;
	}
}