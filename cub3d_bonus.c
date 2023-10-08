/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:32:29 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 00:23:11 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L << 0, key_pressed, init);
	mlx_hook(init->win, 3, 1L << 1, key_release, init);
	mlx_loop_hook(init->mlx, mouse_process, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_init	init;
	int		mouse_y;

	if (init_pars(ac, av, &data) == ERROR)
	{	
		printf("\033[1;31m --> ERROR\n");
		return (1);
	}
	ft_init(&init, &data);
	init.bonus = 1;
	mlx_mouse_get_pos(init.mlx, init.win, &init.mouse_pos, &mouse_y);
	draw_player(&init);
	ft_hook(&init);
	mlx_loop(init.mlx);
	clean_parsing_data(&data);
	printf("\033[1;33m --> VALID\n");
	return (0);
}
