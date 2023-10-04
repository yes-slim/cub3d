/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:35:49 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:36:50 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_convert(const char *s1, int sign)
{
	int				i;
	unsigned long	r;

	r = 0;
	i = 0;
	while (s1[i] >= 48 && s1[i] <= 57)
	{
		if (r > __LONG_MAX__)
			break ;
		r = r * 10 + (s1[i] - '0');
		i++;
	}
	if (r > __LONG_MAX__)
	{
		if (sign < 0)
			return (0);
		return (-1);
	}
	return (r * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_convert(&str[i], sign));
}
