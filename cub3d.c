/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/21 21:14:48 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win);
	exit(0);
}

int	moves_count(int keycode, t_init *init)
{
	if (keycode == 65307)
		ft_exit(init);
	return (0);
}
int	mouse_move(t_init *init)
{

	return (0);
}

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L<<0, moves_count, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
	// mlx_hook(init->win, , mouse_move, init);
}

char **get_map(void)
{
	const char *map="1111111111111111 1000110110111101 1000000000000001 1000000000000001 1000000000000001 1000000000000001 1001101110010001 1111111111111111";
	return (_split(map, ' '));
}

void	draw_map(t_init *init)
{
}

int main(int ac, char **av)
{
	t_init	*init = malloc(sizeof(t_init));
	
	init->map = get_map();
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, screenWidth, screenHeight, "Cub3d");
	draw_map(init);
	ft_hook(init);
	mlx_loop(init->mlx);
}
					  		         
