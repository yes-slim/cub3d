/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes-slim <yes-slim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:36:13 by mberrouk          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:57 by yes-slim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*ft_lstlast(t_map *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_map	*ft_lstnew(void *content)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->row = content;
	new->len = 0;
	return (new);
}

void	ft_lstadd_back(t_map **lst, t_map *new)
{
	t_map	*i;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	i = *lst;
	i = ft_lstlast(i);
	(i)->next = new;
}

void	ft_lstclear(t_map **lst)
{
	t_map	*tmp;

	tmp = NULL;
	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		if (tmp->row)
			free(tmp->row);
		*lst = (*lst)->next;
		free(tmp);
	}
}
