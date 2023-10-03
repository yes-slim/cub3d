/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:28:01 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/03 12:37:03 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_player(int keycode, t_init *init)
{
	double	spd=2.5, oldx = init->px, p_cos=cos(init->pa)*spd, p_sin=sin(init->pa)*spd;	
	if (keycode == KEY_W)//w
	{ 
		if (init->map[(int)(init->py)/CELL][(int)((init->px+p_cos)/CELL)] == '0' )
			init->px += p_cos;
		if (init->map[(int)(init->py + p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py += p_sin;
	}
	if (keycode == KEY_S) //s
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px-p_cos)/CELL)] == '0' )
			init->px -= p_cos;
		if (init->map[(int)(init->py-p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py -= p_sin;
	}
	if (keycode == KEY_D) //d
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px+p_cos)/CELL)] == '0' )
			init->px += p_cos;
		if (init->map[(int)(init->py - p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py -= p_sin;
	}
	if (keycode == KEY_A) //a
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px-p_cos)/CELL)] == '0' )
			init->px -= p_cos;
		if (init->map[(int)(init->py + p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py += p_sin;
	}
	draw_player(init);
	return (0);
}

int move_angel(int keycode, t_init *init)
{
	double sa=get_rad(2.5);
	if (keycode == KEY_ESC)
	ft_exit(init);
	if (keycode == KEY_LEFT) // left
	{
		if (init->pa-sa > 2*M_PI)
			init->pa -= 2*M_PI;
		init->pa -= sa;
	}
	if (keycode == KEY_RIGHT) // right
	{
		if (init->pa+sa < 0)
			init->pa += 2*M_PI;
		init->pa += sa;
	}
	draw_player(init);
	return (0);
}
