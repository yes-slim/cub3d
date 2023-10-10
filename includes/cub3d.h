/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:47:17 by yes-slim          #+#    #+#             */
/*   Updated: 2023/10/10 20:30:09 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

/*****MACROS****/
# define CELL 128
# define FOV 60
# define S_HEI 800
# define S_WID 1366
# define NUM_RAYS S_WID
/*****keyword****/
# define VERTICAL 0
# define HORIZONTAL 1
/*****keycode****/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

typedef struct s_img
{
	void	*img;
	int		img_w;
	int		img_h;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_keys
{
	int	m_d;
	int	m_a;
	int	m_s;
	int	m_w;
	int	m_r;
	int	m_l;
}	t_keys;

typedef struct s_init
{
	void	*mlx;
	void	*win;
	char	**map;
	int		f_clr;
	int		c_clr;
	double	px;
	double	py;
	double	pa;
	int		mh;
	int		mw;
	int		bonus;
	bool	inter;
	double	inter_x;
	double	inter_y;
	double	inter_xh;
	double	inter_yh;
	double	inter_xv;
	double	inter_yv;
	int		mouse_pos;
	t_img	*img;
	t_img	*south;
	t_img	*north;
	t_img	*east;
	t_img	*west;
	t_keys	*keys;
}	t_init;

/****minilibx****/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_pixel_color(t_img *img, int x, int y);

/****helpers****/
void	ft_init(t_init *raycast, t_data *parse);
double	get_rad(double angel);

/****raycast****/
double	dda(t_init *init, double ra);

/****textures****/
t_img	*get_texture(t_init *init, double r_ang);
int		get_texture_x(t_init *init);
int		get_texture_y(t_img *text, double distance, int y);

/****drawing****/
void	draw_walls(t_init *init, double distance, int x, double r_ang);
void	draw_map(t_init *init);
void	draw_player(t_init *init);
void	draw_map_minmap(t_init *init);

/****movement****/
void	ft_hook(t_init *init);
int		move_player(t_init *init);
int		key_pressed(int keycode, t_init *init);
int		key_release(int keycode, t_init *init);
int		mouse_process(int mouse_x, int mouse_y, t_init *init);
int		ft_exit(t_init *init);

#endif
