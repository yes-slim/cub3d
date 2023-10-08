/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:20:34 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 00:20:56 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_text_info(t_init *init, double r_ang, int y, double distance)
{
	t_img	*current_tex;
	int		color;
	int		x_t;
	int		y_t;

	current_tex = get_texture(init, r_ang);
	x_t = get_texture_x(init, current_tex);
	y_t = get_texture_y(current_tex, distance, y);
	color = get_pixel_color(current_tex, x_t, y_t);
	return (color);
}

void	draw_walls(t_init *init, double distance, int x, double r_ang)
{
	int		color;
	int		w_start;
	int		w_end;
	int		y;

	y = 0;
	w_start = (S_HEI / 2 - distance / 2);
	w_end = (S_HEI / 2 + distance / 2);
	if (w_start < 0)
		w_start = 0;
	if (w_end > S_HEI)
		w_end = S_HEI;
	while (y >= 0 && y < w_start)
		my_mlx_pixel_put(init->img, x, y++, init->f_clr);
	while (y >= w_start && y < w_end)
	{
		color = get_text_info(init, r_ang, y, distance);
		my_mlx_pixel_put(init->img, x, y++, color);
	}
	while (y >= w_end && y <= S_HEI)
		my_mlx_pixel_put(init->img, x, y++, init->c_clr);
}

void	draw_player(t_init *init)
{
	int		x;
	int		ray_nb;
	double	rot_a;
	double	distance;
	double	rp1;

	x = 0;
	ray_nb = 0;
	rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
	while (ray_nb < NUM_RAYS)
	{
		rp1 = (init->pa + get_rad(FOV / 2)) - (rot_a * ray_nb);
		if (rp1 > 2 * M_PI)
			rp1 -= 2 * M_PI;
		if (rp1 < 0)
			rp1 += 2 * M_PI;
		distance = dda(init, rp1);
		draw_walls(init, distance, x++, rp1);
		ray_nb++;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->img->img, 0, 0);
	if (init->bonus)
		draw_map_minmap(init);
}

// 	draw_map(init);
// 	mlx_pixel_put(init->mlx, init->win,
// 	init->px/CELL*16, init->py/CELL*16, 0xFF0000);
// 	mlx_pixel_put(init->mlx, init->win,
// 	init->px/CELL*16+1, init->py/CELL*16, 0xFF0000);
// 	mlx_pixel_put(init->mlx, init->win,
// 	init->px/CELL*16, init->py/CELL*16+1, 0xFF0000);
// 	mlx_pixel_put(init->mlx, init->win,
// 	init->px/CELL*16+1, init->py/CELL*16+1, 0xFF0000);
// void	draw_map(t_init *init)
// {
// 	int x=0, y=0;
// 	while (init->map[y/16] && (init->mh*16)>= y)
// 	{
// 		x=0;
// 		while (init->map[y/16][x/16] && (init->mw*16)>= x)
// 		{
// 			// if (!(x%16) || !(y%16))
// 			// 	mlx_pixel_put(init->mlx, init->win, x, y, 0xFFFFFF);
// 			if (init->map[y/16][x/16] == '0')
// 				mlx_pixel_put(init->mlx, init->win, x, y, 0x878787);
// 			else if (init->map[y/16][x/16] == '1')
// 				mlx_pixel_put(init->mlx, init->win, x, y, 0xC09E06);		
// 			x++;
// 		}
// 		y++;
// 	}
// 	double rot_a = get_rad((double)FOV / (double)(NUM_RAYS));
// 	double rx=init->px/CELL*16, ry=init->py/CELL*16; 
// 	int ray_nb=0;
// 	while (ray_nb < NUM_RAYS)
// 	{
// 		rx=init->px/CELL*16, ry=init->py/CELL*16;
// 		double rp1=(init->pa + get_rad(FOV/2)) - (rot_a * ray_nb);
// 		if (init->pa-rot_a > 2*M_PI)
// 			init->pa -= 2*M_PI;
// 		if (init->pa+rot_a < 0)
// 			init->pa += 2*M_PI;
// 		while ((rx>0 && rx < init->mw*16) && (ry>0 && ry < init->mh*16))
// 		{
// 			if (init->map[(int)ry/16][(int)rx/16] != '0')
// 				break;
// 			mlx_pixel_put(init->mlx, init->win, rx, ry, 0x000000);
// 			ry -= sin(rp1);
// 			rx += cos(rp1);
// 		}
// 		ray_nb++;
// 	}
// }
