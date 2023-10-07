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

	tmp_y = 0;
	y = ((init->py / CELL) * size) - mh / 2;
	//if (y <= 0)
	//	y = 0;
	tmp_x = 0;
//	img.img = mlx_new_image(init->mlx, 256, 125);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (tmp_y < mh && y / size < init->mh)
	{
		x = ((init->px / CELL) * size) - mw / 2;
	//	if (x < 0)
	//		x = 0;
		tmp_x = 0;
		while (tmp_x <= mw && x / size < init->mw)
 		{
			put_mmap(init, x, y, size, tmp_y, tmp_x);
			x++;
			tmp_x++;
		}
		y++;
		tmp_y++;
	}

	int py = (mh / 2); //((init->py / CELL) * size) + mh;
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
