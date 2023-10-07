void	draw_map_minmap(t_init *init)
{
	int x;
	int	tmp_x;
	int y;
	int size;
	int mh;
	int mw;
	t_img img;

	mh = 256;
	mw = 125;
	size = 10;
	int tmp_y;

	tmp_y = 0;
	y = init->py - (mh / 2);
	tmp_x = 0;
	img.img = mlx_new_image(init->mlx, 256, 125);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("-x-> %d\n", x);
	while (tmp_y < mh)
	{
		x = init->px - (mw / 2);
		printf("_--x-> %d\n", x);
		while (tmp_x < mw)
		{
			if (init->map[y / size][x / size] == '0')
			{
				my_mlx_pixel_putmmp(&img, x, y, 0x878787);
				//img.addr[(y * img.line_length + x) * (img.bits_per_pixel / 2)] = 0x878787;
			}
			else if (init->map[y / size][x /size] == '1')
				my_mlx_pixel_putmmp(&img, x, y, 0xC09E06);
				//img.addr[(y * img.line_length + x) * (img.bits_per_pixel / 2)] = 0xC09E06;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(init->mlx, init->win, img.img, 0, 0);

}


void	my_mlx_pixel_putmmp(t_img *img, int x, int y, int color)
{
	// printf("x=%d, y=%d\n", x, y);
	char	*dst;

 	if (img == NULL || img->addr == NULL) {
        // Handle invalid img pointer
        return;
    }
	if (x <= 0 && x >  256 &&  y <= 0 && y > 125) {
        // Handle out-of-bounds coordinates
        return;
    }
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (dst == NULL) {
        // Handle invalid destination address
  	  return;
    }
	*(unsigned int*)dst = color;
	
}


