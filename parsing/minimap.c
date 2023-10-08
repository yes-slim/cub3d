#include "../includes/cub3d.h"
#include <mlx.h>
#include <stdio.h>

void	my_mlx_pixel_putmmp(t_img *img, int x, int y, int color);

void	put_mmap(t_init *init, int x, int y, int size, int tmp_y, int tmp_x)
{
	if (y < 0 || x < 0 || y / size < 0 || x / size < 0 || y / size >= init->mh
		|| x / size > init->mw)
				return ;
	else if (init->map[y / size][x / size] == '0')
	{
		mlx_pixel_put(init->mlx, init->win, tmp_x, tmp_y, 0x878787);
	}
	else if (init->map[y / size][x /size] == '1')
		mlx_pixel_put(init->mlx, init->win, tmp_x, tmp_y, 0xC09E06);

}

bool inside_circle(int x, int y, int centerX, int centerY, int radius) {
    int distance;

	distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
    return distance <= radius;
}
void	draw_map_minmap(t_init *init)
{
	int x;
	int	tmp_x;
	int y;
	int size;
	int mh;
	int mw;
	//t_img img;

	mh = 200;
	mw = 250;
	size = 12;
	int tmp_y;
	

	int centerX = mw / 2;
    int centerY = mh / 2;
    int radius = 100;

	tmp_y = 0;
	y = ((init->py / CELL) * size) - mh / 2;
	//if (y <= 0)
	//	y = 0;
	tmp_x = 0;
    
	while (tmp_y < mh && y / size < init->mh)
	{
		x = ((init->px / CELL) * size) - mw / 2;
	//	if (x < 0)
	//		x = 0;
		tmp_x = 0;
		while (tmp_x <= mw && x / size < init->mw)
 		{
			if (inside_circle(tmp_x, tmp_y, centerX, centerY, radius))
				put_mmap(init, x, y, size, tmp_y, tmp_x);
			x++;
			tmp_x++;
		}
		y++;
		tmp_y++;
	}

	/****    draw_map_minmap Borther ****/
	int circangle;

	circangle = 0;
	while (radius < 102)
	{
		circangle = 0;
		while (circangle < 360)
		{
			int x = centerX + radius * cos(circangle * M_PI / 180);
			int y = centerY + radius * sin(circangle * M_PI / 180);
       		
			mlx_pixel_put(init->mlx, init->win, x, y, 0x0000);
			mlx_pixel_put(init->mlx, init->win, x + 1, y, 0x0000);
			mlx_pixel_put(init->mlx, init->win, x - 1, y, 0x0000);
			mlx_pixel_put(init->mlx, init->win, x, y - 1, 0x0000);
			mlx_pixel_put(init->mlx, init->win, x, y + 1, 0x0000);
			mlx_pixel_put(init->mlx, init->win, x + 1, y + 1, 0x0000); 
			mlx_pixel_put(init->mlx, init->win, x - 1, y - 1, 0x0000); 
			circangle++;
		}
		radius++;
    }


	/**** draw_map_minmap Player ****/
	int py = (mh / 2);
	int px = (mw / 2);
	
	int yy;
	int xx;

	yy = py - 3;
	while (yy < py + 3)
	{
		xx = px - 3;
		while (xx < px + 3)
		{
			mlx_pixel_put(init->mlx, init->win, xx, yy, 0xFF0000);
			xx++;
		}
		yy++;
	}

}
