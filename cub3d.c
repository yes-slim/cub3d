/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/08 23:05:49 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(t_init *init);

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
	mlx_mouse_get_pos(init.mlx, init.win, &init.mouse_pos, &mouse_y);
	draw_player(&init);
	ft_hook(&init);
	mlx_loop(init.mlx);
	clean_parsing_data(&data);
	printf("\033[1;33m --> VALID\n");
	return (0);
}
