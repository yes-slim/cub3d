/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:09:31 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 20:43:46 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_process(int mouse_x, int mouse_y, t_init *init)
{
	double	sa;

	sa = get_rad(6);
	if (mouse_x < 0 || mouse_x > S_WID || mouse_y < 0 || mouse_y > S_HEI)
		return (0);
	if (init->mouse_pos != mouse_x)
	{
		if (init->mouse_pos > mouse_x)
		{
			if (init->pa + sa > 2 * M_PI)
				init->pa -= 2 * M_PI;
			init->pa += sa;
		}
		else
		{
			if (init->pa - sa < 0)
				init->pa += 2 * M_PI;
			init->pa -= sa;
		}
		init->mouse_pos = mouse_x;
		move_player(init);
	}
	return (0);
}
