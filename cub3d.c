/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/27 00:06:52 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win);
	exit(0);
}
// void	draw_ray()

int	player_move(int keycode, t_init *init)
{
	int sp = 2;
	if (keycode == KEY_ESC)
		ft_exit(init);	
	if (keycode == KEY_W) //w
		if (init->map[(int)(init->py-sp)/cell][(int)init->px/cell] == '0')
			init->py -= sp;
	if (keycode == KEY_S) //s
		if (init->map[((int)init->py+sp)/cell][(int)init->px/cell] == '0')
			init->py += sp;
	if (keycode == KEY_D) //d
		if (init->map[(int)init->py/cell][((int)init->px+sp)/cell] == '0')
			init->px += sp;
	if (keycode == KEY_A) //a
		if (init->map[(int)init->py/cell][((int)init->px-sp)/cell] == '0')
			init->px -= sp;
	// if (keycode == KEY_UP) // up
		
	// if (keycode == KEY_DOWN) // down

	// if (keycode == KEY_LEFT) // left

	// if (keycode == KEY_RIGHT) // right
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
	const char *map="1111111111111111 1000110110111101 1000000100000001 1000010000100001 1000100010000001 1000000001000001 1001101110010001 1111111111111111";
	// const char *map="111 101 101 111";	
	return (_split(map, ' '));
}
void	draw_player(t_init *init)
{
	mlx_pixel_put(init->mlx, init->win, init->px, init->py, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px, init->py+1, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py+1, 0x000000);
}

void	draw_map(t_init *init)
{
	int x=0, y=0;
	while (init->map[y/cell] && (init->mh*cell)>= y)
	{
		x=0;
		while (init->map[y/cell][x/cell] && (init->mw*cell)>= x)
		{
			if (!(x%cell) || !(y%cell))
				mlx_pixel_put(init->mlx, init->win, x, y, 0xFFFFFF);
			else if (init->map[y/cell][x/cell] == '0')
				mlx_pixel_put(init->mlx, init->win, x, y, 0x878787);
			else if (init->map[y/cell][x/cell] == '1')
				mlx_pixel_put(init->mlx, init->win, x, y, 0xC09E06);
			
			x++;
		}
		y++;
	}
	draw_player(init);
	// mlx_put_image_to_window(init->mlx, init->win, init->pl, init->px, init->py);
}

int main(int ac, char **av)
{
	t_init	*init = malloc(sizeof(t_init));
	
	int h=12;
	int w=12;
	init->map = get_map();
	init->mh = 8, init->mw =strlen(init->map[0]);
	init->py = (init->mh * cell / 2) - (cell / 2), init->px = (init->mw * cell / 2) - (cell /2);
	// init->py = 128, init->px = 96;
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, screen_wid, screen_hei, "Cub3d");
	// init->pl = mlx_xpm_file_to_image(init->mlx, "./raycasting/player.xpm", &h, &w);
	draw_map(init);
	ft_hook(init);
	mlx_loop(init->mlx);
}
					  		         
