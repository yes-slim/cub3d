/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:47:17 by yes-slim          #+#    #+#             */
/*   Updated: 2023/09/28 15:51:10 by yes-slim         ###   ########.fr       */
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

# define CELL 32
# define FOV 60
# define POV -90
# define NUM_RAYS 1
# define S_HEI 768
# define S_WID 1536
/*****keycode****/
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_init
{
	void	*mlx;
	void	*win;
	char	**map;
	// void	*pl;
	double	px;
	double	py;
	double	pa;
	int		mh;
	int		mw;
}	t_init;


/*****minilibx****/

/*****helpers****/
void	draw_map(t_init *init);
/*****libft****/
char	*get_next_line(int fd);
char	**_split(char const *s, char c);
char	*_strjoin(char const *s1, char const *s2);
size_t	_strlen(const char *str);
char	*_strdup(const char *src);

#endif