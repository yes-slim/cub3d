/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:09:31 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/08 21:29:12 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_process(t_init *init)
{
	int mouse_x;
	int mouse_y;
	double sa;

	sa = get_rad(3);
	mlx_mouse_get_pos(init->mlx, init->win, &mouse_x, &mouse_y);
	if (init->mouse_pos != mouse_x)
	{
		if (init->mouse_pos > mouse_x)
		{
			if (init->pa + sa > 2*M_PI)
				init->pa -= 2*M_PI;
			init->pa += sa;
		}
		else
		{
			if (init->pa - sa < 0)
				init->pa += 2*M_PI;
			init->pa -= sa;

		}
		init->mouse_pos = mouse_x;
		move_player(init);
	}
	return (0);
}
