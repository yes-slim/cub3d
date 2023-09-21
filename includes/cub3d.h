/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:47:17 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/21 21:13:41 by yes-slim         ###   ########.fr       */
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

# define cell 32
# define screenHeight 512
# define screenWidth 1024
// # define 
// # define 
// # define 
typedef struct s_init
{
	void	*mlx;
	void	*win;
	char	**map;
}	t_init;


/*****minilibx****/
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
/*****libft****/
char	**_split(char const *s, char c);

#endif