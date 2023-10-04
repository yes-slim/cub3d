/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:38:23 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:24 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H
 
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
 
# define BUFFER_SIZE 1024
# define ERROR 0
# define VALID 1
# define WHITESPACE(c) ((c >= 9 && c <= 13) || c == 32)
# define ISNUMERIC(c) (c >= '0' && c <= '9')

enum Textures 
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
	char		**mp;
	char		**textures;
	int			len_map;
	int			F;
	int			C;
	float		x;
	float		y;
    t_map		*map;
}   t_data;

/****check_errors.c****/
int check_extension_file(char *str);
int	check_map(t_data *data, int len, int j);

/****get_next_line.c****/
char	*get_next_line(int fd);

/****str_utils.c****/
int		ft_strlen(char *str);
int		ft_strchr(char *s, char c);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strjoin(char *s1, char *s2, int len);
char	*ft_strdup(char *s1);

/****parsing.c****/
int		parsing_file(int fd, t_data *data, int row, int countarg);
int		get_data(t_data *data, char *arg, int flag);
void	fetch_map(t_data *data, char *line, int *row_index);

/****ft_atoi.c****/
int	ft_atoi(const char *str);

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
int	check_arg(t_data *data, char *line);
int	get_floor_ceiling(t_data *data, char *arg, int flag);
int	floor_ceiling_value(char *arg, int comma, int conver, int i);
int	convert_rgb(char *arg, int conver);
int	valid_form(char *arg, int j, int comma);

/****check_errors_utils.c****/
int	map_component(char c);
int	valid_space(t_data *data, int x, int y);

#endif
