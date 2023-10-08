/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:20:34 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 17:23:36 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_init *init, double distance, int x, double r_ang)
{
	int w_start = (S_HEI/2 - distance/2);
	int w_end = (S_HEI/2 + distance/2);

	int y = 0;
	if (w_start < 0)
		w_start = 0;
	if (w_end > S_HEI)
		w_end = S_HEI;
	while (y>=0 && y < w_start)
		my_mlx_pixel_put(init->img, x, y++, init->F_clr);
	while (y >= w_start && y < w_end)
	{
		(void)r_ang;
		t_img *current_tex = get_texture(init, r_ang);
		int x_t = get_texture_x(init, current_tex);
		int y_t = get_texture_y(init, current_tex, distance, y);
		int color = get_pixel_color(current_tex, x_t, y_t);
		my_mlx_pixel_put(init->img, x, y++, color);
	}
	while (y>=w_end && y <= S_HEI)
		my_mlx_pixel_put(init->img, x, y++, init->C_clr);
}

void	draw_map_minmap(t_init *init);
void	draw_player(t_init *init)
{
	int x=0, ray_nb=0;
	double rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
	double distance;
	double rp1=init->pa+rot_a - get_rad(FOV/2);
	while (ray_nb < NUM_RAYS)
	{
		distance = dda(init, rp1);
		draw_walls(init, distance, x++, rp1);
		rp1 += rot_a;
		ray_nb++;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->img->img, 0, 0);
	draw_map_minmap(init);
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
