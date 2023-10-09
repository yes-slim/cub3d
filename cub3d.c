/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 23:42:37 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L << 0, key_pressed, init);
	mlx_hook(init->win, 3, 1L << 1, key_release, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_init	init;

	if (init_pars(ac, av, &data) == ERROR)
	{	
		printf("\033[1;31m --> ERROR\n");
		return (1);
	}
	ft_init(&init, &data);
	init.bonus = 0;
	draw_player(&init);
	ft_hook(&init);
	mlx_loop(init.mlx);
	clean_parsing_data(&data);
	return (0);
}
