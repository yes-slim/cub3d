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

#include "cub3d.h"

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
	data->fd[flag] = open(arg, O_RDONLY);
	if (data->fd[flag] < 0)
		return (-1);
	return (VALID);
}

int	fetch_map(t_data *data, char *line, int *row_index)
{
	int	i;

	i = 0;
	while (WHITESPACE(line[i]))
		i++;
	if (!line[i])
	{
		if (*row_index)
		{
			free(line);
			return (ERROR);
		}
	}
	else
	{
		ft_lstadd_back(&data->map, ft_lstnew(ft_strdup(line)));
		*row_index += 1;
	}
	return (VALID);
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
			if (flag == -1)
			{
				free(line);
				return (ERROR);
			}
			countarg += flag;
		}
		else
			if (fetch_map(data, line, &row) == ERROR)
				return (ERROR);
		free(line);
	}
	return (countarg == 6 && check_map(data, row, 0));
}
