/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:24:20 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 03:53:33 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(t_init *init, double r_ang)
{
	if (init->inter == VERTICAL)
	{
		if (cos(r_ang) > 0)
			return (init->East);
		else
			return (init->West);
	}
	else if (init->inter == HORIZONTAL)
	{
		if (sin(r_ang) < 0)
			return (init->North);
		else
			return (init->South);
	}
	return (NULL);
}

int	get_texture_x(t_init *init, t_img *text)
{
	int x=0;
	
	if (init->inter == VERTICAL)
		x = init->inter_y;
	if (init->inter == HORIZONTAL)
		x = init->inter_x;
	x %= CELL;
	x = x * text->img_w / CELL;
	return (x);
}

int	get_texture_y(t_init *init, t_img *text, double distance, int y)
{
	int y_t;
	int distancefromtop;

	(void)init;
	distancefromtop = y + (distance/2) - (S_HEI/2) ;
	y_t = distancefromtop / distance * text->img_h;
	return (y_t);
}
