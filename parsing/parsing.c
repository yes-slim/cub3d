/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:15:22 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:57 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"

int	check_opening_files(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_errmsg(NULL);
		perror(path);
		return (-2);
	}
	close(fd);
	return (VALID);
}

int	get_data(t_data *data, char *arg, int flag)
{
	int	i;
	int	len;

	i = 0;
	while (WHITESPACE(arg[i]))
		i++;
	len = ft_strlen(&arg[i]);
	if (!len)
		return (-1);
	len--;
	while (len && WHITESPACE(arg[len]))
	{
		arg[len] = '\0';
		len--;
	}
	if (len < 3 || ft_strcmp(&arg[len - 3], ".xpm" ))
		return (-1);
	if (check_opening_files(&arg[i]) == -2)
		return (-2);
	data->textures[flag] = ft_strdup(arg); 
	return (VALID);
}

void	fetch_map(t_data *data, char *line, int *row_index)
{
	int	i;

	i = 0;
	while (WHITESPACE(line[i]))
		i++;
	if (!line[i] && !*row_index)
		return ;
	else
	{
		ft_lstadd_back(&data->map, ft_lstnew(ft_strdup(line)));
		*row_index += 1;
	}
}

int	parsing_file(int fd, t_data *data, int row, int countarg)
{
	char	*line;
	int		flag;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (countarg < 6)
		{
			flag = check_arg(data, line);
			if (flag < 0)
			{
				free(line);
				return (flag);
			}
			countarg += flag;
		}
		else
			fetch_map(data, line, &row);
		free(line);
	}
	return (countarg == 6 && check_map(data, row, 0));
}
