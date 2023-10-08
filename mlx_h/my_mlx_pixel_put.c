/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:05:07 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/09 00:24:58 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (img == NULL || img->addr == NULL)
		return ;
	if (x <= 0 && x > S_WID && y <= 0 && y > S_HEI)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (dst == NULL)
		return ;
	*(unsigned int *)dst = color;
}
