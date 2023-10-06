/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:18:19 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/06 16:40:35 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dda_v(t_init *init, double ra)
{
	double 	dis_v;	
	double ver_x;
	double ver_y;
	
	ver_x = (int)(init->px/CELL + (cos(ra) > 0)) * CELL;
	ver_y = tan(ra)*(ver_x - init->px) + init->py;
	while ((ver_x>0 && ver_x < init->mw*CELL) && (ver_y>0 && ver_y < init->mh*CELL))
	{
		if (init->map[(int)ver_y/CELL][(int)ver_x/CELL] == '1')
			break ;
		if (init->map[(int)ver_y/CELL][(int)ver_x/CELL -1] == '1')
			break ;
		ver_x -= CELL;
		if (cos(ra) > 0)
			ver_x += 2*CELL;
		ver_y = tan(ra)*(ver_x - init->px) + init->py;
	}
	dis_v = sqrt((ver_x-init->px)*(ver_x-init->px) + (ver_y-init->py)*(ver_y-init->py));
	init->inter_x = ver_x;
	init->inter_y = ver_y;
	return (dis_v);
}

double	dda_h(t_init *init, double ra)
{
	double 	dis_h;
	double	hor_y;
	double	hor_x;

	hor_y = (int)(init->py/CELL + (sin(ra) > 0)) * CELL;
	hor_x = (hor_y - init->py) / tan(ra) + init->px;
	while ((hor_x > 0 && hor_x < init->mw*CELL) && (hor_y>0 && hor_y < init->mh*CELL))
	{
		if (init->map[(int)hor_y/CELL][(int)hor_x/CELL] == '1')
			break ;
		if (init->map[(int)hor_y/CELL -1][(int)hor_x/CELL] == '1')
			break ;
		hor_y += CELL;
		if (sin(ra) < 0)
			hor_y -= 2*CELL;
		hor_x = (hor_y - init->py) / tan(ra) + init->px;
		
	}
	dis_h = sqrt((hor_x-init->px)*(hor_x-init->px) + (hor_y-init->py)*(hor_y-init->py));
	init->inter_x = hor_x;
	init->inter_y = hor_y;
	return (dis_h);
}

double	dda(t_init *init, double ra)
{
	double	dis;
	double	w_hei;
	double	dis_v;
	double	dis_h;	
	
	dis_v = dda_v(init, ra);
	dis_h = dda_h(init, ra);
	if (dis_h > dis_v)
	{
		dis = dda_v(init, ra);
		init->inter	= VERTICAL;
	}
	else
	{
		dis = dda_h(init, ra);
		init->inter = HORIZONTAL;	
	}
	dis *= cos(ra - init->pa);
    w_hei = (S_HEI * 30) / dis;
	return (w_hei);
}
