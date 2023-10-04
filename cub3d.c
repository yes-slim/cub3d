/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/04 17:53:30 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

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
	int y;
	
	y = 0;
	while (y>=0 && y<(S_HEI/2 - distance/2))
		my_mlx_pixel_put(init->img, x, y++, 0xFFB87D);
	while (y>=(S_HEI/2 - distance/2) && y <(S_HEI/2 + distance/2))
		my_mlx_pixel_put(init->img, x, y++, 0x4F003F);
	while (y>=(S_HEI/2 + distance/2) && y <=S_HEI)
		my_mlx_pixel_put(init->img, x, y++, 0x83E3FF);
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
		if (init->pa > 2*M_PI)
			init->pa -= 2*M_PI;
		if (init->pa < 0)
			init->pa += 2*M_PI;
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
	while (rp1 <= rp2)
	{
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
	}
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
	init->keys = malloc(sizeof(t_keys));
	init->map = get_map();
	init->mh = 15, init->mw =strlen(init->map[0]);
	init->px = 1*CELL + CELL/2, init->py =5*CELL + CELL/2 ;
	init->pa = get_rad(90);
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, S_WID, S_HEI, "Cub3d");
	init->img->img = mlx_new_image(init->mlx, S_WID, S_HEI);
	init->img->addr = mlx_get_data_addr(init->img->img, &init->img->bits_per_pixel, &init->img->line_length, &init->img->endian);
	draw_player(init);
	ft_hook(init);
	mlx_loop(init->mlx);
	
	// t_data	data;
	// if (init_pars(ac, av, &data) == ERROR)
	//  	return (1);
	// printf("c -> %d\n", data.C);
	// printf("f -> %d\n", data.F);
	// clean_parsing_data(&data);
	// return (0);
}
