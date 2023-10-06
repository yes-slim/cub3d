/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:28:01 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 00:42:27 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_pressed(int keycode, t_init *init)
{
	if (keycode == KEY_ESC)
		ft_exit(init);
	if (keycode == KEY_W)//w
		init->keys->m_W = 1; 
	if (keycode == KEY_S) //s
		init->keys->m_S = 1; 
	if (keycode == KEY_D) //d
		init->keys->m_D = 1;
	if (keycode == KEY_A) //a
		init->keys->m_A = 1;
	if (keycode == KEY_LEFT) // left
		init->keys->m_L = 1;
	if (keycode == KEY_RIGHT) // right
		init->keys->m_R = 1;
	move_player(init);
	return (0);
}

int key_release(int keycode, t_init *init)
{
	if (keycode == KEY_W)//w
		init->keys->m_W = 0; 
	if (keycode == KEY_S) //s
		init->keys->m_S = 0; 
	if (keycode == KEY_D) //d
		init->keys->m_D = 0;
	if (keycode == KEY_A) //a
		init->keys->m_A = 0;
	if (keycode == KEY_LEFT) // left
		init->keys->m_L = 0;
	if (keycode == KEY_RIGHT) // right
		init->keys->m_R = 0;
	return (0);
}

void	move_angel(t_init *init)
{
	double sa;
	
	sa=get_rad(5);
	if (init->keys->m_L == 1) // left
	{
		if (init->pa-sa > 2*M_PI)
			init->pa -= 2*M_PI;
		init->pa -= sa;
	}
	if (init->keys->m_R == 1) // right
	{
		if (init->pa+sa < 0)
			init->pa += 2*M_PI;
		init->pa += sa;
	}
}
void	move(t_init *init, double *p_cos, double *p_sin, int spd)
{
	if (init->keys->m_W == 1)//w
	{
		*p_cos=cos(init->pa)*spd;
		*p_sin=sin(init->pa)*spd;
	}
	if (init->keys->m_S == 1) //s
	{
		*p_cos=cos(init->pa - M_PI)*spd;
		*p_sin=sin(init->pa - M_PI)*spd;
	}
	if (init->keys->m_D == 1) //d
	{
		*p_cos=cos(init->pa + M_PI/2)*spd;
		*p_sin=sin(init->pa + M_PI/2)*spd;
	}
	if (init->keys->m_A == 1) //a
	{
		*p_cos=cos(init->pa - M_PI/2)*spd;
		*p_sin=sin(init->pa - M_PI/2)*spd;
	}
}

int	move_player(t_init *init)
{
	double	oldx;
	double	p_sin;
	double	p_cos;
	int		spd;
	
	oldx = init->px;
	p_cos=0;
	p_sin=0;
	spd = 4;
	if (init->keys->m_W == 1 || init->keys->m_S == 1 ||
		init->keys->m_D == 1 || init->keys->m_A == 1)
		move(init, &p_cos, &p_sin, spd);
	if (init->map[(int)(init->py + 5 + p_sin) / CELL][(int)(oldx / CELL)] != '1' &&
		init->map[(int)(init->py - 5 + p_sin) / CELL][(int)(oldx / CELL)] != '1')
		init->py += p_sin;
	if (init->map[(int)(init->py) / CELL][(int)((init->px + 5 + p_cos) / CELL)] != '1' &&
		init->map[(int)(init->py) / CELL][(int)((init->px - 5 + p_cos) / CELL)] != '1')
		init->px += p_cos;
	move_angel(init);
	draw_player(init);
	return (0);
}
