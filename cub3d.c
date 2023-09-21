/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/21 22:53:08 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win);
	exit(0);
}

int	player_move(int keycode, t_init *init)
{
	if (keycode == 65307)
		ft_exit(init);
	if (keycode == 119) //w
		if (init->py - 4 >= 0 && init->map[(init->py-4)/cell][init->px/cell] == '0')
			init->py -= 4;
	if (keycode == 115) //s
		if (init->py + 4 <= init->mh * cell && init->map[(init->py+4+12)/cell][init->px/cell] == '0')
			init->py += 4;
	if (keycode == 100) //d
		if (init->px + 4 <= init->mw * cell && init->map[init->py/cell][(init->px+4+12)/cell] == '0')
			init->px += 4;
	if (keycode == 97) //a
		if (init->px - 4 >= 0 && init->map[init->py/cell][(init->px-4)/cell] == '0')
			init->px -= 4;
	draw_map(init);
	return (0);
}

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L<<0, player_move, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
	// mlx_hook(init->win, , player_move, init);
}

int	mouse_move(t_init *init)
{

	return (0);
}

char **get_map(void)
{
	const char *map="1111111111111111 1000110110111101 1000000100000001 1000010000100001 1000100010000001 1000000000000001 1001101110010001 1111111111111111";
	return (_split(map, ' '));
}

void	draw_map(t_init *init)
{
	int x=0, y=0;
	while ((init->mh*cell) >= y)
	{
		x=0;
		while ((init->mw*cell) >= x)
		{
			if (!(x%cell) || !(y%cell))
				mlx_pixel_put(init->mlx, init->win, x, y, 0xFFFFFF);
			else if (init->map[y/cell][x/cell] == '1')
				mlx_pixel_put(init->mlx, init->win, x, y, 0xC09E06);
			else
				mlx_pixel_put(init->mlx, init->win, x, y, 0x878787);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->pl, init->px, init->py);
}

int main(int ac, char **av)
{
	t_init	*init = malloc(sizeof(t_init));
	
	int h=12;
	int w=12;
	init->map = get_map();
	init->mh = 8, init->mw =strlen(init->map[0]);
	init->py = (init->mh * cell / 2) - cell / 2 - 6, init->px = (init->mw * cell / 2) -6;
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, screen_wid, screen_hei, "Cub3d");
	init->pl = mlx_xpm_file_to_image(init->mlx, "./raycasting/player.xpm", &h, &w);
	draw_map(init);
	ft_hook(init);
	mlx_loop(init->mlx);
}
					  		         
