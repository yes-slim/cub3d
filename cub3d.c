/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/06 23:43:33 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(t_init *init, double r_ang)
{
	if (init->inter == VERTICAL)
	{
		if (cos(r_ang) > 0)
			return (init->East);
		
			return (init->West);
	}
	if (init->inter == HORIZONTAL)
	{
		if (sin(r_ang) < 0)
			return (init->North);
		else
			return (init->South);
	}
	return (NULL);
}

int	get_texture_x(t_init *init, t_img *text)
{
	int x=0;
	
	if (init->inter == VERTICAL)
		x = init->inter_y;
	if (init->inter == HORIZONTAL)
		x = init->inter_x;
	x %= CELL;
	x = x * text->img_w / CELL;
	return (x);
}

int	get_texture_y(t_init *init, t_img *text, double distance, int y)
{
	int y_t;
	int distancefromtop;

	distancefromtop = y + (distance/2) - (S_HEI/2) ;
	y_t = distancefromtop / distance * text->img_h;
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

void	draw_walls(t_init *init, double distance, int x, int r_ang)
{
	int w_start = (S_HEI/2 - distance/2);
	int w_end = (S_HEI/2 + distance/2);

	int y = 0;
	if (w_start < 0)
		w_start = 0;
	if (w_end > S_HEI)
		w_end = S_HEI;
	while (y>=0 && y < w_start)
		my_mlx_pixel_put(init->img, x, y++, 0xFFBC62);
	while (y >= w_start && y < w_end)
	{
		t_img *current_tex = get_texture(init, r_ang);
		int x_t = get_texture_x(init, current_tex);
		int y_t = get_texture_y(init, current_tex, distance, y);
		int color = get_pixel_color(current_tex, x_t, y_t);
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
	double rp1=init->pa+rot_a - get_rad(FOV/2), rp2=init->pa + get_rad(FOV/2);
	while (rp1 <= rp2)
	{
		if (init->pa > 2 * M_PI)
			init->pa -= 2 * M_PI;
		if (init->pa < 0)
			init->pa += 2 * M_PI;
		distance = dda(init, rp1);
		draw_walls(init, distance, x, rp1);
		x++;
		rp1 += rot_a;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->img->img, 0, 0);
	// draw_map(init);
	// mlx_pixel_put(init->mlx, init->win, init->px/CELL*16, init->py/CELL*16, 0xFF0000);
	// mlx_pixel_put(init->mlx, init->win, init->px/CELL*16+1, init->py/CELL*16, 0xFF0000);
	// mlx_pixel_put(init->mlx, init->win, init->px/CELL*16, init->py/CELL*16+1, 0xFF0000);
	// mlx_pixel_put(init->mlx, init->win, init->px/CELL*16+1, init->py/CELL*16+1, 0xFF0000);
}

void	draw_map(t_init *init)
{
	int x=0, y=0;
	while (init->map[y/16] && (init->mh*16)>= y)
	{
		x=0;
		while (init->map[y/16][x/16] && (init->mw*16)>= x)
		{
			// if (!(x%16) || !(y%16))
			// 	mlx_pixel_put(init->mlx, init->win, x, y, 0xFFFFFF);
			if (init->map[y/16][x/16] == '0')
				mlx_pixel_put(init->mlx, init->win, x, y, 0x878787);
			else if (init->map[y/16][x/16] == '1')
				mlx_pixel_put(init->mlx, init->win, x, y, 0xC09E06);
			
			x++;
		}
		y++;
	}
	double rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
	double rp1=init->pa - get_rad(FOV/2), rp2=init->pa + get_rad(FOV/2);
	double rx=init->px/CELL*16, ry=init->py/CELL*16; 
	while (rp1 <= rp2)
	{
		rx=init->px/CELL*16, ry=init->py/CELL*16;
		while ((rx>0 && rx < init->mw*16) && (ry>0 && ry < init->mh*16))
		{
			if (init->map[(int)ry/16][(int)rx/16] != '0')
				break;
			mlx_pixel_put(init->mlx, init->win, rx, ry, 0x000000);
			ry += sin(rp1);
			rx += cos(rp1);
		}
		if (init->pa-rot_a > 2*M_PI)
			init->pa -= 2*M_PI;
		if (init->pa+rot_a < 0)
			init->pa += 2*M_PI;
		rp1 += rot_a;
	}
}

int main(int ac, char **av)
{
	t_data	data;
	t_init	init;
	
	if (init_pars(ac, av, &data) == ERROR)
	{	
		printf("\033[1;31m --> ERROR\n");
		return (1);
	}
	printf("c -> %d\n", data.C);
	printf("f -> %d\n", data.F);
	printf("x -> %f\n", data.x);
	printf("y -> %f\n", data.y);
	printf("data.map_h -> %d\n", data.map_h);
	printf("data.map_w -> %d\n", data.map_w);
	printf("data.angel -> %f\n", data.angel);
	printf("<------------ textures paths : ----------->\n");
	printf("WE: %s\n", data.textures[WE]);
	printf("SO: %s\n", data.textures[SO]);
	printf("NO: %s\n", data.textures[NO]);
	printf("EA: %s\n", data.textures[EA]);
	printf("<------------ map : ----------->\n");
	for (int i = 0; data.mp[i]; i++)
		dprintf(open("file", O_CREAT | O_APPEND | O_RDWR, 0777), "%s\n", data.mp[i]);
	ft_init(&init, &data);
	draw_player(&init);
	ft_hook(&init);
	mlx_loop(init.mlx);
	clean_parsing_data(&data);
	printf("\033[1;33m --> VALID\n");
	return (0);
}
