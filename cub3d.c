/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:20:00 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/02 21:23:53 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	double	spd=4, sa=get_rad(5), oldx = init->px, p_cos=cos(init->pa)*spd, p_sin=sin(init->pa)*spd;
	if (keycode == KEY_ESC)
		ft_exit(init);	
	if (keycode == KEY_W)//w
	{ 
		if (init->map[(int)(init->py)/CELL][(int)((init->px+p_cos)/CELL)] == '0' )
			init->px += p_cos;
		if (init->map[(int)(init->py + p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py += p_sin;
	}
	if (keycode == KEY_S) //s
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px-p_cos)/CELL)] == '0' )
			init->px -= p_cos;
		if (init->map[(int)(init->py-p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py -= p_sin;
	}
	if (keycode == KEY_D) //d
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px+p_cos)/CELL)] == '0' )
			init->px += p_cos;
		if (init->map[(int)(init->py - p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py -= p_sin;
	}
	if (keycode == KEY_A) //a
	{
		if (init->map[(int)(init->py)/CELL][(int)((init->px-p_cos)/CELL)] == '0' )
			init->px -= p_cos;
		if (init->map[(int)(init->py + p_sin)/CELL][(int)(oldx/CELL)] == '0' )
			init->py += p_sin;
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
	draw_player(init);
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

double	dda_v(t_init *init, double ra)
{
	double 	dis_v;	
	double ver_x = (int)(init->px/CELL + (cos(ra) > 0)) * CELL;
	double ver_y = tan(ra)*(ver_x - init->px) + init->py;
	while ((ver_x>0 && ver_x < init->mw*CELL) && (ver_y>0 && ver_y < init->mh*CELL))
	{
		if (init->map[(int)ver_y/CELL][(int)ver_x/CELL] == '1')
			break ;
		if (init->map[(int)ver_y/CELL][(int)ver_x/CELL -1] == '1')
			break ;
		ver_x -= CELL;
		if (cos(ra) > 0)
			ver_x += 2*CELL;
		ver_y = tan(ra)*(ver_x - init->px) + init->py;
	}
	dis_v = sqrt((ver_x-init->px)*(ver_x-init->px) + (ver_y-init->py)*(ver_y-init->py));
	return (dis_v);
}

double	dda_h(t_init *init, double ra)
{
	double 	dis_h;
	double	ver_y = (int)(init->py/CELL + (sin(ra) > 0)) * CELL;
	double	ver_x = (ver_y - init->py) / tan(ra) + init->px;
	while ((ver_x>0 && ver_x < init->mw*CELL) && (ver_y>0 && ver_y < init->mh*CELL))
	{
		if (init->map[(int)ver_y/CELL][(int)ver_x/CELL] == '1')
			break ;
		if (init->map[(int)ver_y/CELL -1][(int)ver_x/CELL] == '1')
			break ;
		ver_y += CELL;
		if (sin(ra) < 0)
			ver_y -= 2*CELL;
		ver_x = (ver_y - init->py) / tan(ra) + init->px;
		
	}
	dis_h = sqrt((ver_x-init->px)*(ver_x-init->px) + (ver_y-init->py)*(ver_y-init->py));
	return (dis_h);
}

double	dda(t_init *init, double ra)
{
	double	dis, dis_v, dis_h;	
	dis_v = dda_v(init, ra);
	dis_h = dda_h(init, ra);
	if (dis_h > dis_v)
		dis = dis_v;
	else
		dis = dis_h;
	return (dis);
}

void	draw_walls(t_init *init, double distance, int x)
{
	int y=0;
	while (y>=0 && y<(S_HEI/2 - distance/2))
		my_mlx_pixel_put(init->img, x, y++, 0xFFB87D);
	while (y>=(S_HEI/2 - distance/2) && y <(S_HEI/2 + distance/2))
		my_mlx_pixel_put(init->img, x, y++, 0xFF7DB4);
	while (y>=(S_HEI/2 + distance/2) && y <S_HEI)
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
		distance = dda(init, rp1);
		draw_walls(init, distance, x);
		x++;
		if (init->pa-rot_a > 2*M_PI)
			init->pa -= 2*M_PI;
		if (init->pa+rot_a < 0)
			init->pa += 2*M_PI;
		rp1 += rot_a;
	}
	mlx_put_image_to_window(init->mlx, init->win, init->img->img, 0, 0);
	draw_map(init);
	mlx_pixel_put(init->mlx, init->win, init->px, init->py, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px, init->py+1, 0x000000);
	mlx_pixel_put(init->mlx, init->win, init->px+1, init->py+1, 0x000000);
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
			ry += sin(rp1);
			rx += cos(rp1);
		}
		if (init->pa-rot_a > 2*M_PI)
			init->pa -= 2*M_PI;
		if (init->pa+rot_a < 0)
			init->pa += 2*M_PI;
		rp1 += rot_a;
	}
	// draw_player(init);
}

char **get_map(void)
{
	int i=1, fd=open("./maps/map.cub", O_RDWR);
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
	int h=12;
	int w=12;
	init->map = get_map();
	init->mh = 8, init->mw =strlen(init->map[0]);
	init->px = 10*CELL + CELL/2, init->py =6*CELL + CELL/2 ;
	init->pa = get_rad(POV);
	// init->py = 128, init->px = 96;
	init->mlx = mlx_init();
	init->win = mlx_new_window(init->mlx, S_WID, S_HEI, "Cub3d");
	init->img->img = mlx_new_image(init->mlx, S_WID, S_HEI);
	init->img->addr = mlx_get_data_addr(init->img->img, &init->img->bits_per_pixel, &init->img->line_length, &init->img->endian);
	draw_player(init);
	ft_hook(init);
	mlx_loop(init->mlx);
	// t_data	data;

	// if (init_pars(ac, av, &data) == ERROR)
	// 	return (1);
	// clean_parsing_data(&data);
	// return (0);
}
