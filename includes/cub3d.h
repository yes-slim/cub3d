/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:47:17 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/02 21:25:00 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "parsing.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define CELL 16
# define FOV 60
# define POV -90
# define S_HEI 768
# define S_WID 1536
# define NUM_RAYS S_WID
/*****keycode****/
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_init
{
	void	*mlx;
	void	*win;
	char	**map;
	double	px;
	double	py;
	double	pa;
	int		mh;
	int		mw;
	t_img	*img;
}	t_init;

/****minilibx****/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
/****helpers****/
void	draw_map(t_init *init);
void	draw_player(t_init *init);
/****libft****/
char	*_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif