/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 02:56:09 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_hook(init->win, 17, 0, ft_exit, init);
}

int main(int ac, char **av)
	t_data	data;
	t_init	init;
	
	if (init_pars(ac, av, &data) == ERROR)
	{	
		printf("\033[1;31m --> ERROR\n");
		return (1);
	}
	// printf("c -> %d\n", data.C);
	// printf("f -> %d\n", data.F);
	// printf("x -> %f\n", data.x);
	// printf("y -> %f\n", data.y);
	// printf("data.map_h -> %d\n", data.map_h);
	// printf("data.map_w -> %d\n", data.map_w);
	// printf("data.angel -> %f\n", data.angel);
	// printf("<------------ textures paths : ----------->\n");
	// printf("WE: %s\n", data.textures[WE]);
	// printf("SO: %s\n", data.textures[SO]);
	// printf("NO: %s\n", data.textures[NO]);
	// printf("EA: %s\n", data.textures[EA]);
	// printf("<------------ map : ----------->\n");
	// for (int i = 0; data.mp[i]; i++)
	// 	printf("%s\n", data.mp[i]);
	ft_init(&init, &data);
	draw_player(&init);
	ft_hook(&init);
	mlx_loop(init.mlx);
	clean_parsing_data(&data);
  printf("\033[1;33m --> VALID\n");
	return (0);
}
