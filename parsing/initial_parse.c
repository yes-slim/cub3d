/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:36:05 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/08 22:21:42 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_errmsg(char *msg)
{
	int	i;

	i = 0;
	i += write(STDERR_FILENO, "Error\n", 6);
	if (msg && *msg)
	{
		i += write(STDERR_FILENO, msg, ft_strlen(msg));
		i += write(STDERR_FILENO, "\n", 1);
	}
	return (ERROR);
}

int	init_parsing_data(t_data *data)
{
	int	i;

	i = 0;
	data->map = NULL;
	data->mp = NULL;
	data->textures = malloc(sizeof(char *) * 5);
	if (!data->textures)
		return (ERROR);
	while (i < 5)
		data->textures[i++] = NULL;
	data->len_map = 0;
	data->f = -1;
	data->c = -1;
	data->map_h = 0;
	data->map_w = 0;
	return (VALID);
}

void	clean_parsing_data(t_data *data)
{
	int	i;

	if (data->mp != NULL)
	{
		i = 0;
		while (data->mp[i])
		{
			free(data->mp[i]);
			i++;
		}
		free(data->mp);
	}
	i = 0;
	while (i < 5)
	{
		if (data->textures[i] != NULL)
			free(data->textures[i]);
		i++;
	}
	free(data->textures);
	ft_lstclear(&(data->map));
}

int	init_pars(int ac, char *av[], t_data *data)
{
	int		fd;
	int		flag;

	if (ac != 2 || ft_strcmp(&(av[1][ft_strlen(av[1]) - 4]), ".cub"))
		return (print_errmsg("Usage: ./cub3D <your map>.cub"));
	fd = open(av[1], O_RDONLY);
	if (fd < 3)
	{
		print_errmsg(NULL);
		perror(av[1]);
		return (ERROR);
	}
	init_parsing_data(data);
	flag = parsing_file(fd, data, 0, 0);
	if (flag <= 0)
	{
		if (flag != -2)
			print_errmsg("Invalid args");
		clean_parsing_data(data);
		return (ERROR);
	}
	return (VALID);
}
