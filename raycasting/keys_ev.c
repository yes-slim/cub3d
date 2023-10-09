/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:28:01 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 15:43:22 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mv_ud(double p_sin);
int	get_mv_rl(double p_cos);

int	key_pressed(int keycode, t_init *init)
{
	if (keycode == KEY_ESC)
		ft_exit(init);
	if (keycode == KEY_W)
		init->keys->m_w = 1;
	if (keycode == KEY_S)
		init->keys->m_s = 1;
	if (keycode == KEY_D)
		init->keys->m_d = 1;
	if (keycode == KEY_A)
		init->keys->m_a = 1;
	if (keycode == KEY_LEFT)
		init->keys->m_l = 1;
	if (keycode == KEY_RIGHT)
		init->keys->m_r = 1;
	move_player(init);
	return (0);
}

int	key_release(int keycode, t_init *init)
{
	if (keycode == KEY_W)
		init->keys->m_w = 0;
	if (keycode == KEY_S)
		init->keys->m_s = 0;
	if (keycode == KEY_D)
		init->keys->m_d = 0;
	if (keycode == KEY_A)
		init->keys->m_a = 0;
	if (keycode == KEY_LEFT)
		init->keys->m_l = 0;
	if (keycode == KEY_RIGHT)
		init->keys->m_r = 0;
	return (0);
}

void	move_angel(t_init *init)
{
	double	sa;

	sa = get_rad(10);
	if (init->keys->m_l == 1)
	{
		if (init->pa - sa > 2 * M_PI)
			init->pa -= 2 * M_PI;
		init->pa += sa;
	}
	if (init->keys->m_r == 1)
	{
		if (init->pa + sa < 0)
			init->pa += 2 * M_PI;
		init->pa -= sa;
	}
}

void	move(t_init *init, double *p_cos, double *p_sin)
{
	if (init->keys->m_w == 1)
	{
		*p_cos = cos(init->pa);
		*p_sin = sin(init->pa);
	}
	if (init->keys->m_s == 1)
	{
		*p_cos = cos(init->pa - M_PI);
		*p_sin = sin(init->pa - M_PI);
	}
	if (init->keys->m_d == 1)
	{
		*p_cos = cos(init->pa - M_PI / 2);
		*p_sin = sin(init->pa - M_PI / 2);
	}
	if (init->keys->m_a == 1)
	{
		*p_cos = cos(init->pa + M_PI / 2);
		*p_sin = sin(init->pa + M_PI / 2);
	}
}

int	move_player(t_init *init)
{
	double	p_sin;
	double	p_cos;
	int		spd;

	p_cos = 0;
	p_sin = 0;
	spd = 15;
	if (init->keys->m_w == 1 || init->keys->m_s == 1
		|| init->keys->m_d == 1 || init->keys->m_a == 1)
		move(init, &p_cos, &p_sin);
	if (init->map[(int)(init->py - get_mv_ud(p_sin) + p_sin)
		/ CELL][(int)(init->px / CELL)] != '1')
		init->py -= p_sin * spd;
	if (init->map[(int)(init->py) / CELL]
		[(int)((init->px + get_mv_rl(p_cos) + p_cos) / CELL)] != '1')
		init->px += p_cos * spd;
	move_angel(init);
	draw_player(init);
	return (0);
}
