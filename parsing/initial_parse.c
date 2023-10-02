/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:36:05 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 14:23:45 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_errmsg(char *msg)
{
	int i;

	i = write(STDERR_FILENO, "Error\n", 6);
	if (msg && *msg)
	{
		i += write(STDERR_FILENO, msg, ft_strlen(msg));
		i += write(STDERR_FILENO, "\n", 1);
		return (i);
	}
	return (ERROR);
}

int	init_parsing_data(t_data *data)
{
	int	i;

	data->map = NULL;
	data->mp = NULL;
	data->len_map = 0;
	i = 0;
	while (i < 4)
		data->fd[i++] = 0;
	data->F = -1;
	data->C = -1;
	return (VALID);
}

void	clean_parsing_data(t_data *data)
{
	int	i;

	if (data->mp != NULL)
	{
		i = 0;
		while (data->mp[i])
			free(data->mp[i++]);
		free(data->mp);
	}
	i = 0;
	while (i < 4)
	{
		if (data->fd[i] > 2)
			close(data->fd[i]);
		i++;
	}
	ft_lstclear(&(data->map));
}

int	init_pars(int ac, char *av[], t_data *data)
{
	int		fd;

	if (ac != 2 ||!check_extension_file(av[1]))
		return (print_errmsg("Invalid args"));
	fd = open(av[1], O_RDONLY);
	if (fd < 3)
	{
		print_errmsg(NULL);
		perror(av[1]);
		return (ERROR);
	}
	if (!init_parsing_data(data) || parsing_file(fd, data, 0, 0) == ERROR)
	{
		print_errmsg("Invalid args");
		clean_parsing_data(data);
		return (ERROR);
	}
	return (VALID);
}
