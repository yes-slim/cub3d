/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:24:20 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/10 17:17:01 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(t_init *init, double r_ang)
{
	if (init->inter == HORIZONTAL)
	{
		if (sin(r_ang) < 0)
			return (init->south);
		else
			return (init->north);
	}
	else if (init->inter == VERTICAL)
	{
		if (cos(r_ang) > 0)
			return (init->east);
		else
			return (init->west);
	}
	return (NULL);
}

int	get_texture_x(t_init *init)
{
	int	x;

	x = 0;
	if (init->inter == HORIZONTAL)
		x = init->inter_x;
	if (init->inter == VERTICAL)
		x = init->inter_y;
	x %= CELL;
	return (x);
}

int	get_texture_y(t_img *text, double distance, int y)
{
	int	y_t;
	int	distancefromtop;

	distancefromtop = y + (distance / 2) - (S_HEI / 2);
	y_t = distancefromtop * text->img_h / distance;
	return (y_t);
}
