/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:05:07 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/02 23:35:04 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	// printf("x=%d, y=%d\n", x, y);
	char	*dst;

 	if (img == NULL || img->addr == NULL) {
        // Handle invalid img pointer
        return;
    }
	if (x <= 0 && x > S_WID  &&  y <= 0 && y > S_HEI) {
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

// void my_mlx_pixel_put(t_img img, int x, int y, int color)
// {
//     if (img == NULL  img->addr == NULL) {
//         // Handle invalid img pointer
//         return;
//     }

//     if (x < 0  x >= img->width  y < 0  y >= img->height) {
//         // Handle out-of-bounds coordinates
//         return;
//     }

//     char dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));

//     if (dst == NULL) {
//         // Handle invalid destination address
//         return;
//     }

//     (unsigned int)dst = color;
// }