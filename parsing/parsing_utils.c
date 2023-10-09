/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:21:02 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/08 22:22:10 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	valid_form(char *arg, int j, int comma)
{
	if (comma > 2)
		return (false);
	if (arg[j] != ',' && ((arg[j] < '0' || arg[j] > '9') \
						&& (!is_space(arg[j]))))
		return (false);
	if ((arg[j] == ',' && (!arg[j + 1] || arg[j + 1] == ','\
						|| arg[j + 1] == '\n' || (arg[j + 1] < '0'\
						|| arg[j + 1] > '9'))))
		return (false);
	return (true);
}

int	convert_rgb(char *arg, int conver)
{
	int	i;
	int	value;

	i = 0;
	while (is_space(arg[i]))
		i++;
	value = ft_atoi(&arg[i]);
	if (!arg[i] || value < 0 || value > 255)
	{
		return (-1);
	}
	return (value << conver);
}

int	floor_ceiling_value(char *arg, int comma, int conver, int i)
{
	int	j;
	int	result;

	j = i;
	result = 0;
	while (arg[j])
	{
		if (!valid_form(arg, j, comma))
			return (-1);
		j++;
		if (arg[j] == ',' || !arg[j])
		{
			if (arg[j])
			{
				arg[j++] = '\0';
				comma++;
			}
			if (pars_fc_value(arg, i, &conver, &result) == -1)
				return (-1);
			i = j;
		}
	}
	if (comma != 2)
		return (-1);
	return (result);
}

int	get_floor_ceiling(t_data *data, char *arg, int flag)
{
	int	i;
	int	value;

	i = 0;
	while (is_space(arg[i]))
		i++;
	value = floor_ceiling_value(arg, 0, 16, i);
	if (value == -1)
		return (-1);
	if (flag == F)
		data->f = value;
	else
		data->c = value;
	return (1);
}

int	check_arg(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(line[i]))
		i++;
	if (!line[i])
		return (0);
	while (line[i + j] && !is_space(line[i + j]))
		j++;
	line[i + j++] = '\0';
	if (!ft_strcmp(&line[i], "NO") && !data->textures[NO])
		return (get_data(data, &line[i + j], NO));
	if (!ft_strcmp(&line[i], "SO") && !data->textures[SO])
		return (get_data(data, &line[i + j], SO));
	if (!ft_strcmp(&line[i], "WE") && !data->textures[WE])
		return (get_data(data, &line[i + j], WE));
	if (!ft_strcmp(&line[i], "EA") && !data->textures[EA])
		return (get_data(data, &line[i + j], EA));
	if (!ft_strcmp(&line[i], "F") && data->f == -1)
		return (get_floor_ceiling(data, &line[i + j], F));
	if (!ft_strcmp(&line[i], "C") && data->c == -1)
		return (get_floor_ceiling(data, &line[i + j], C));
	return (-1);
}
