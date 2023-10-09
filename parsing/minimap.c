/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:24:17 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/09 00:24:19 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_mmap(t_init *init, t_coordinate point, t_coordinate index)
{
	if (point.y < 0 || point.x < 0 || point.y / MINI_CEL < 0 \
		|| point.x / MINI_CEL < 0 || point.y / MINI_CEL >= init->mh \
		|| point.x / MINI_CEL > init->mw)
		return ;
	else if (init->map[point.y / MINI_CEL][point.x / MINI_CEL] == '0')
	{
		mlx_pixel_put(init->mlx, init->win, index.x, index.y, 0x878787);
	}
	else if (init->map[point.y / MINI_CEL][point.x / MINI_CEL] == '1')
		mlx_pixel_put(init->mlx, init->win, index.x, index.y, 0xC09E06);
}

void	draw_line(t_init *init, double x0, double y0, t_coordinate p1)
{
	int		steps;
	int		i;
	double	xindex;
	double	yindex;

	if (fabs(p1.x - x0) >= fabs(p1.y - y0))
		steps = fabs(p1.x - x0);
	else
		steps = fabs(p1.y - y0);
	xindex = (p1.x - x0) / steps;
	yindex = (p1.y - y0) / steps;
	i = 0;
	while (i < steps)
	{
		mlx_pixel_put(init->mlx, init->win, round(x0) \
				, round(y0), P_COLOR);
		x0 += xindex;
		y0 += yindex;
		i++;
	}
}

void	draw_mmap_border(t_init *init)
{
	int	border;
	int	segments;
	int	x;
	int	y;
	int	i;

	i = 0;
	segments = 2000;
	border = MINI_RAD;
	while (border < 104)
	{
		i = 0;
		while (i < 2000)
		{
			x = M_CEN_X + border * cos(2 * M_PI * i / segments);
			y = M_CEN_Y + border * sin(2 * M_PI * i / segments);
			mlx_pixel_put(init->mlx, init->win, x, y, P_COLOR);
			i++;
		}
		border++;
	}
}

void	draw_mmap_player(t_init *init)
{
	t_coordinate	centrep;
	t_coordinate	p1;
	t_coordinate	p2;
	t_coordinate	p3;
	double			angle;

	centrep.x = M_CEN_X;
	centrep.y = M_CEN_Y;
	angle = init->pa * -1;
	p1.x = M_CEN_X + P_SIZE * cos(angle);
	p1.y = M_CEN_Y + P_SIZE * sin(angle);
	p2.x = M_CEN_X + P_SIZE * cos(angle + (2.0 * M_PI / 3.0));
	p2.y = M_CEN_Y + P_SIZE * sin(angle + (2.0 * M_PI / 3.0));
	p3.x = M_CEN_X + P_SIZE * cos(angle + (4.0 * M_PI / 3.0));
	p3.y = M_CEN_Y + P_SIZE * sin(angle + (4.0 * M_PI / 3.0));
	draw_line(init, M_CEN_X, M_CEN_Y, p3);
	draw_line(init, p3.x, p3.y, p1);
	draw_line(init, p1.x, p1.y, p2);
	draw_line(init, p2.x, p2.y, centrep);
	draw_mmap_border(init);
}

void	draw_map_minmap(t_init *init)
{
	t_coordinate	index;
	t_coordinate	point;

	index.y = 0;
	point.y = ((init->py / CELL) * MINI_CEL) - MINI_H / 2;
	while (index.y < MINI_H && point.y / MINI_CEL < init->mh)
	{
		point.x = ((init->px / CELL) * MINI_CEL) - MINI_W / 2;
		index.x = 0;
		while (index.x <= MINI_W && point.x / MINI_CEL < init->mw)
		{
			if (inside_circle(index.x, index.y))
				put_mmap(init, point, index);
			point.x++;
			index.x++;
		}
		point.y++;
		index.y++;
	}
	draw_mmap_player(init);
}
