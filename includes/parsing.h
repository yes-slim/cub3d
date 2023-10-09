/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:38:23 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/09 11:47:30 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

# define ERROR 0
# define VALID 1

/*** mini map macros ***/
# define MINI_H 250
# define MINI_W 250
# define MINI_CEL 12
# define P_SIZE 6
# define P_COLOR 0x000000
# define MINI_RAD 100
# define M_CEN_X 125
# define M_CEN_Y 125

enum e_Textures
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
};

typedef struct s_map
{
	char			*row;
	int				len;
	struct s_map	*next;
}	t_map;

typedef struct s_data
{
	char	**mp;
	char	**textures;
	int		len_map;
	int		f;
	int		c;
	double	x;
	double	y;
	int		map_w;
	int		map_h;
	double	angel;
	t_map	*map;
}	t_data;

typedef struct s_coordinate
{
	int	x;
	int	y;
}	t_coordinate;

/****check_errors.c****/
int		check_extension_file(char *str);
int		check_map(t_data *data, int len, int j);
int		convert_listmap(t_data *data, int j);
void	direc_angle(t_data *data, char symbol);

/****get_next_line.c****/
char	*get_next_line(int fd);

/****str_utils_1.c****/
int		ft_strlen(char *str);
int		ft_strlcpy(char *dest, char *src, int dstsize);
int		ft_strchr(char *s, char c);
int		ft_strcmp(char *str1, char *str2);
int		is_space(char c);

/****str_utils.c****/
char	*ft_strjoin(char *s1, char *s2, int len);
char	*ft_strdup(char *s1);

/****parsing.c****/
int		parsing_file(int fd, t_data *data, int row, int countarg);
int		get_data(t_data *data, char *arg, int flag);
void	fetch_map(t_data *data, char *line, int *row_index);

/****ft_atoi.c****/
int		ft_atoi(const char *str);

/****linked_list.c****/
void	ft_lstadd_back(t_map **lst, t_map *new);
t_map	*ft_lstnew(void *content);
t_map	*ft_lstlast(t_map *lst);
void	ft_lstclear(t_map **lst);

/****initial_parse.c****/
int		init_parsing_data(t_data *data);
void	clean_parsing_data(t_data *data);
int		init_pars(int ac, char *av[], t_data *data);
int		print_errmsg(char *msg);

/****parsing_utils.c****/
int		check_arg(t_data *data, char *line);
int		get_floor_ceiling(t_data *data, char *arg, int flag);
int		floor_ceiling_value(char *arg, int comma, int conver, int i);
int		convert_rgb(char *arg, int conver);
bool	valid_form(char *arg, int j, int comma);

/****check_errors_utils.c****/
int		map_component(char c);
int		valid_space(t_data *data, int x, int y);

/****parsing_utils_1.c****/
void	trim_spaces(t_data *data);
bool	inside_circle(int x, int y);

/****check_errors_1.c****/
int		pars_fc_value(char *arg, int i, int *conver, int *result);
int		check_space_comp(t_data *data);
int		set_player_info(t_data *data, t_coordinate p, int *flag);
int		check_position(t_data *data, int y, int x);

#endif
