/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/28 12:17:37 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check(t_init *init)
{
	printf("=================================\n");
	printf("*px === %f*\n*py === %f*\n*pa === %f*\n", init->px, init->py, init->pa);
	printf("=================================\n");
}
int	ft_exit(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win);
	exit(0);
}

double get_rad(double angel)
{
	return (angel * M_PI / 180);
}

int	player_move(int keycode, t_init *init)
{
	float sa=get_rad(5);
	double p_cos=cos(init->pa)*2, p_sin=sin(init->pa)*2;
	if (keycode == KEY_ESC)
		ft_exit(init);	
	if (keycode == KEY_W) //w
		if (init->map[(int)(init->py+p_sin)/CELL][(int)((init->px+p_cos)/CELL)] == '0')
		{
			init->py += p_sin;
			init->px += p_cos;
		}
	if (keycode == KEY_S) //s
		if (init->map[(int)(init->py-p_sin)/CELL][(int)((init->px-p_cos)/CELL)] == '0')
		{
			init->py -= p_sin;
			init->px -= p_cos;
		}
	if (keycode == KEY_D) //d
		if (init->map[(int)(init->py+p_cos)/CELL][(int)((init->px-p_sin)/CELL)] == '0')
		{
			init->px -= p_sin;
			init->py += p_cos;
		}
	if (keycode == KEY_A) //a
		if (init->map[(int)(init->py-p_cos)/CELL][(int)((init->px+p_sin)/CELL)] == '0')
		{
			init->px += p_sin;
			init->py -= p_cos;
		}
	if (keycode == KEY_LEFT) // left
	{
		if (init->pa-sa > 2*M_PI)
			init->pa -= 2*M_PI;
		init->pa -= sa;
	}
	if (keycode == KEY_RIGHT) // right
	{
		if (init->pa+sa < 0)
			init->pa += 2*M_PI;
		init->pa += sa;
	}
	ft_check(init);
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
	double rot_a = get_rad(5);
	double rx=init->px, ry=init->py;
	double rp1=init->pa - get_rad(FOV/2), rp2=init->pa + get_rad(FOV/2);
	// while (rp1 <= rp2)
	// {
		rx=init->px, ry=init->py;
		while ((rx>0 && rx < init->mw*CELL) && (ry>0 && ry < init->mh*CELL))
		{
			mlx_pixel_put(init->mlx, init->win, rx, ry, 0xD70000);
			ry += sin(init->pa);
			rx += cos(init->pa);
		}
	// 	if (init->pa-rot_a > 2*M_PI)
	// 		init->pa -= 2*M_PI;
	// 	if (init->pa+rot_a < 0)
	// 		init->pa += 2*M_PI;
	// 	rp1 += rot_a;		
	// }
}

void	draw_map(t_init *init)
{
	int x=0, y=0;
	while (init->map[y/CELL] && (init->mh*CELL)>= y)
	{
		x=0;
		while (init->map[y/CELL][x/CELL] && (init->mw*CELL)>= x)
		{
			if (!(x%CELL) || !(y%CELL))
				mlx_pixel_put(init->mlx, init->win, x, y, 0xFFFFFF);
			else if (init->map[y/CELL][x/CELL] == '0')
				mlx_pixel_put(init->mlx, init->win, x, y, 0x878787);
			else if (init->map[y/CELL][x/CELL] == '1')
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
	init->py = (init->mh * CELL / 2) - (CELL / 2), init->px = (init->mw * CELL / 2) - (CELL /2);
	init->pa = -M_PI /2;
	// init->py = 128, init->px = 96;
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, S_WID, S_HEI, "Cub3d");
	// init->pl = mlx_xpm_file_to_image(init->mlx, "./raycasting/player.xpm", &h, &w);
	draw_map(init);
	ft_hook(init);
	mlx_loop(init->mlx);
}
					  		         
