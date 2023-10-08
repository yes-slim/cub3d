/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:54:10 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/08 22:55:23 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mv_ud(double p_sin)
{
	int	mv_ud;

	mv_ud = 0;
	if (p_sin)
		mv_ud = 15 * (p_sin / fabs(p_sin));
	return (mv_ud);
}

int	get_mv_rl(double p_cos)
{
	int	mv_rl;

	mv_rl = 0;
	if (p_cos)
		mv_rl = 15 * (p_cos / fabs(p_cos));
	return (mv_rl);
}

int	ft_exit(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win);
	exit(0);
}

double get_rad(double angel)
{
	return (angel * M_PI / 180);
}

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L<<0, key_pressed, init);
	mlx_hook(init->win, 3, 1L<<1, key_release, init);
	mlx_loop_hook(init->mlx, mouse_process, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
}
