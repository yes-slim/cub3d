/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:01:27 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 23:41:58 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_null(t_init *raycast)
{
	if (!raycast->north->img || !raycast->south->img
		|| !raycast->west->img || !raycast->east->img)
	{
		printf("Error\ninvlaide xpm file\n");
		printf("\033[1;31m --> ERROR\n");
		exit (0);
	}
}

void	ft_init_textures(t_init *raycast, t_data *parse)
{
	raycast->north->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[NO], &raycast->north->img_w,
			&raycast->north->img_h);
	raycast->south->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[SO], &raycast->south->img_w,
			&raycast->south->img_h);
	raycast->east->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[EA], &raycast->east->img_w,
			&raycast->east->img_h);
	raycast->west->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[WE], &raycast->west->img_w,
			&raycast->west->img_h);
	check_null(raycast);
	raycast->north->addr = mlx_get_data_addr(raycast->north->img,
			&raycast->north->bits_per_pixel, &raycast->north->line_length,
			&raycast->north->endian);
	raycast->south->addr = mlx_get_data_addr(raycast->south->img,
			&raycast->south->bits_per_pixel, &raycast->south->line_length,
			&raycast->south->endian);
	raycast->east->addr = mlx_get_data_addr(raycast->east->img,
			&raycast->east->bits_per_pixel, &raycast->east->line_length,
			&raycast->east->endian);
	raycast->west->addr = mlx_get_data_addr(raycast->west->img,
			&raycast->west->bits_per_pixel, &raycast->west->line_length,
			&raycast->west->endian);
}

void	ft_init(t_init *raycast, t_data *parse)
{
	raycast->img = malloc(sizeof(t_img));
	raycast->keys = malloc(sizeof(t_keys));
	raycast->north = malloc(sizeof(t_img));
	raycast->south = malloc(sizeof(t_img));
	raycast->east = malloc(sizeof(t_img));
	raycast->west = malloc(sizeof(t_img));
	raycast->c_clr = parse->c;
	raycast->f_clr = parse->f;
	raycast->map = parse->mp;
	raycast->mh = parse->map_h;
	raycast->mw = parse->map_w;
	raycast->px = parse->x;
	raycast->py = parse->y;
	raycast->pa = parse->angel;
	raycast->mlx = mlx_init();
	ft_init_textures(raycast, parse);
	raycast->win = mlx_new_window(raycast->mlx, S_WID, S_HEI, "Cub3d");
	raycast->img->img = mlx_new_image(raycast->mlx, S_WID, S_HEI);
	raycast->img->addr = mlx_get_data_addr(raycast->img->img,
			&raycast->img->bits_per_pixel, &raycast->img->line_length,
			&raycast->img->endian);
}
