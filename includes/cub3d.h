/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:47:17 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/26 23:48:42 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define cell 32
# define FOV 60
# define PI 3.14159265359
# define PA 90*PI/180
# define screen_hei 512
# define screen_wid 1024
/*****keycode****/
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 653623
# define KEY_ESC 65307

typedef struct s_init
{
	void	*mlx;
	void	*win;
	char	**map;
	// void	*pl;
	float	px;
	float	py;
	int		mh;
	int		mw;
}	t_init;


/*****minilibx****/

/*****helpers****/
void	draw_map(t_init *init);
/*****libft****/
char	**_split(char const *s, char c);
#endif