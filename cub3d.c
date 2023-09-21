/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/21 15:00:08 by yes-slim         ###   ########.fr       */
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

char **get_map(void)
{
	// const char *map="1111111111111111 1000110110111101 1000000000000001 1000000000000001 1000000000000001 1000000000000001 1001101110010001 1111111111111111";
	const char *map="1";
	return (_split(map, ' '));
}

void	draw_map(t_init *init)
{
	int x=0, y=0;
	int i=0, j=0;
	// while (init->map[i])
	// {
	// 	j = 0;
	// 	while (init->map[i][j])
	// 	{
			while (y <= init->screenHeight)
			{
				x = 0;
				while (x <= init->screenWidth)
				{
					int i = x/32;
					int j = y/32;
					printf("i=%d, j=%d\n", i, j);
					if (!(x%32) || !(y%32))
						mlx_pixel_put(init->mlx, init->win, x, y, 0xFF0000);
					else if (init->map[j][i] == 1)
						mlx_pixel_put(init->mlx, init->win, x, y, 0x0093FF);
					else if (init->map[j][i] == 0)
						mlx_pixel_put(init->mlx, init->win, x, y, 0xFF0000);
					x++;
				}
				y++;
			}
	// 		j++;
	// 	}
	// 	i++;
	// }
	printf("finish map\n");
}

int main(int ac, char **av)
{
	t_init	*init = malloc(sizeof(t_init));
	
	init->map = get_map();
	int i=0; while (init->map[i++]);
	init->screenHeight = --i * 32;
	init->screenWidth = strlen(init->map[0]) * 32;
	printf("%d, %d\n", init->screenWidth, init->screenHeight);
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, init->screenWidth, init->screenHeight, "Cub3d");
	init->img = mlx_new_image(init->mlx, init->screenWidth, init->screenHeight);
	draw_map(init);
	mlx_hook(init->win, 2, 1L<<0, moves_count, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
	mlx_loop(init->mlx);
}
					  		         
