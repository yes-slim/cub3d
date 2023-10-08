/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:24:20 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 16:54:39 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(t_init *init, double r_ang)
{
	if (init->inter == HORIZONTAL)
	{
		if (r_ang > get_rad(0) && r_ang < get_rad(180))
			return (init->South);
		else
			return (init->North);
	}
	else if (init->inter == VERTICAL)
	{
		if (r_ang < get_rad(90) && r_ang > get_rad(270))
			return (init->East);
		else
			return (init->West);
	}
	return (NULL);
}

int	get_texture_x(t_init *init, t_img *text)
{
	int x=0;
	
	if (init->inter == HORIZONTAL)
		x = init->inter_x;
	if (init->inter == VERTICAL)
		x = init->inter_y;
	x %= CELL;
	if (!text)
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
