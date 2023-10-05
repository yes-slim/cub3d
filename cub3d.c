/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/05 20:12:19 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_x(t_init *init)
{
	int x=0;
	
	if (init->inter == VERTICAL)
		x=init->inter_y;
	if (init->inter == HORIZONTAL)
		x=init->inter_x;
	x %= CELL;
	x = x * init->brick->img_w / CELL;
	return (x);
}

int	get_texture_y(t_init *init, double distance, int y)
{
	int y_t;
	int distancefromtop = y + (distance/2) - (S_HEI/2) ;
	y_t = distancefromtop / distance * init->brick->img_h;
	return (y_t);
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

void	ft_hook(t_init *init)
{
	mlx_hook(init->win, 2, 1L<<0, key_pressed, init);
	mlx_hook(init->win, 3, 1L<<1, key_release, init);
	mlx_hook(init->win, 17, 0, ft_exit, init);
}

int	mouse_move(t_init *init)
{

	return (0);
}

void	draw_walls(t_init *init, double distance, int x)
{
	int w_start = (S_HEI/2 - distance/2);
	int w_end = (S_HEI/2 + distance/2);
	if (w_start < 0)
		w_start = 0;
	if (w_end > S_HEI)
		w_end = S_HEI;
	int y;
	int x_t = get_texture_x(init), y_t;
	y = 0;
	while (y>=0 && y < w_start)
		my_mlx_pixel_put(init->img, x, y++, 0xFFBC62);
	while (y >= w_start && y < w_end)
	{
		y_t = get_texture_y(init, distance, y);
		int color = get_pixel_color(init->brick, x_t, y_t);
		my_mlx_pixel_put(init->img, x, y++, color);
	}
	while (y>=w_end && y <= S_HEI)
		my_mlx_pixel_put(init->img, x, y++, 0x62B3FF);
}

void	draw_player(t_init *init)
{
	int x=0;
	double rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
	double distance, dis_v, dis_h;
	double p_sin = sin(init->pa), p_cos=cos(init->pa);
	double rp1=init->pa - get_rad(FOV/2), rp2=init->pa + get_rad(FOV/2);
	while (rp1 <= rp2)
	{
		if (init->pa > 2 * M_PI)
			init->pa -= 2 * M_PI;
		if (init->pa < 0)
			init->pa += 2 * M_PI;
		distance = dda(init, rp1);
		draw_walls(init, distance, x);
		x++;
		rp1 += rot_a;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->img->img, 0, 0);
	draw_map(init);
	mlx_pixel_put(init->mlx, init->win, init->px, init->py, 0xFF0000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py, 0xFF0000);
	mlx_pixel_put(init->mlx, init->win, init->px, init->py+1, 0xFF0000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py+1, 0xFF0000);
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
	double rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
	double rp1=init->pa - get_rad(FOV/2), rp2=init->pa + get_rad(FOV/2);
	double rx=init->px, ry=init->py; 
	// while (rp1 <= rp2)
	// {
		rx=init->px, ry=init->py;
		while ((rx>0 && rx < init->mw*CELL) && (ry>0 && ry < init->mh*CELL))
		{
			if (init->map[(int)ry/CELL][(int)rx/CELL] != '0')
				break;
			mlx_pixel_put(init->mlx, init->win, rx, ry, 0x000000);
			ry += sin(init->pa);
			rx += cos(init->pa);
		}
		if (init->pa-rot_a > 2*M_PI)
			init->pa -= 2*M_PI;
		if (init->pa+rot_a < 0)
			init->pa += 2*M_PI;
		rp1 += rot_a;
	// }
}

char **get_map(void)
{
	int i=1, fd=open("./maps/m.cub", O_RDWR);
	char *map = NULL, *buff = get_next_line(fd);
	while (buff)
	{
		buff = _strjoin(buff, "\n");
		map = _strjoin(map, buff);
		buff = get_next_line(fd);
	}
	return (ft_split(map, '\n'));
}

int main(int ac, char **av)
{
	t_init	*init = malloc(sizeof(t_init));
	init->img = malloc(sizeof(t_img));
	init->brick = malloc(sizeof(t_img));
	init->keys = malloc(sizeof(t_keys));
	init->map = get_map();
	init->mh = 15, init->mw =strlen(init->map[0]);
	init->px = 13*CELL + CELL/2, init->py =7*CELL + CELL/2 ;
	init->pa = get_rad(-90);
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, S_WID, S_HEI, "Cub3d");
	init->img->img = mlx_new_image(init->mlx, S_WID, S_HEI);
	init->img->addr = mlx_get_data_addr(init->img->img, &init->img->bits_per_pixel, &init->img->line_length, &init->img->endian);
	init->brick->img = mlx_xpm_file_to_image(init->mlx, "./textures/Bricks.xpm", &init->brick->img_w, &init->brick->img_h);
	init->brick->addr = mlx_get_data_addr(init->brick->img, &init->brick->bits_per_pixel, &init->brick->line_length, &init->brick->endian);
	draw_player(init);
	ft_hook(init);
	mlx_loop(init->mlx);
/*=============================================================================================*/
	// t_data	data;
	//  if (init_pars(ac, av, &data) == ERROR)
	// {	
	// 	//printf("\033[1;31m --> ERROR\n");
	// 	return (1);
	// }
	// printf("c -> %d\n", data.C);
	// printf("f -> %d\n", data.F);
	// printf("x -> %f\n", data.x);
	// printf("y -> %f\n", data.y);
	// for (int i = 0; data.mp[i]; i++)
	// {
	// 	printf("%s\n", data.mp[i]);
	// }
	// clean_parsing_data(&data);
	// printf("\033[1;33m --> VALID\n");
	// return (0);
}
