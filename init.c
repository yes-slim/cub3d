/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:01:27 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/07 01:48:32 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_textures(t_init *raycast, t_data *parse)
{
	raycast->North->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[NO], &raycast->North->img_w,
			&raycast->North->img_h);
	raycast->North->addr = mlx_get_data_addr(raycast->North->img,
			&raycast->North->bits_per_pixel, &raycast->North->line_length,
			&raycast->North->endian);
	raycast->South->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[SO], &raycast->South->img_w,
			&raycast->South->img_h);
	raycast->South->addr = mlx_get_data_addr(raycast->South->img,
			&raycast->South->bits_per_pixel, &raycast->South->line_length,
			&raycast->South->endian);
	raycast->East->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[EA], &raycast->East->img_w,
			&raycast->East->img_h);
	raycast->East->addr = mlx_get_data_addr(raycast->East->img,
			&raycast->East->bits_per_pixel, &raycast->East->line_length,
			&raycast->East->endian);
	raycast->West->img = mlx_xpm_file_to_image(raycast->mlx,
			parse->textures[WE], &raycast->West->img_w,
			&raycast->West->img_h);
	raycast->West->addr = mlx_get_data_addr(raycast->West->img,
			&raycast->West->bits_per_pixel, &raycast->West->line_length,
			&raycast->West->endian);
}

void	ft_init(t_init *raycast, t_data *parse)
{
	raycast->img = malloc(sizeof(t_img));
	raycast->img = malloc(sizeof(t_img));
	raycast->keys = malloc(sizeof(t_keys));
	raycast->North = malloc(sizeof(t_img));
	raycast->South = malloc(sizeof(t_img));
	raycast->East = malloc(sizeof(t_img));
	raycast->West = malloc(sizeof(t_img));
	raycast->C_clr = parse->C;
	raycast->F_clr = parse->F;
	raycast->map = parse->mp;
	raycast->mh = parse->map_h;
	raycast->mw = parse->map_w;
	raycast->px = parse->x;
	raycast->py = parse->y;
	raycast->pa = parse->angel;
	raycast->mlx = mlx_init();
	raycast->win = mlx_new_window(raycast->mlx, S_WID, S_HEI, "Cub3d");
	raycast->img->img = mlx_new_image(raycast->mlx, S_WID, S_HEI);
	raycast->img->addr = mlx_get_data_addr(raycast->img->img,
			&raycast->img->bits_per_pixel, &raycast->img->line_length,
			&raycast->img->endian);
	ft_init_textures(raycast, parse);
}
