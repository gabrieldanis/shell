/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:36 by dberes            #+#    #+#             */
/*   Updated: 2024/01/04 14:33:50 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	list_size(t_plist **lst)
{
	int		count;
	t_plist	*ptr;

	count = 0;
	ptr = *lst;
	if (lst == NULL)
		return (0);
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

t_plist	*list_last(t_plist **lst)
{
	t_plist	*ptr;

	if (lst == NULL)
		return (*lst);
	ptr = *lst;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}

void	add_pipe_node(t_plist **lst, t_plist *new)
{
	t_plist	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = list_last(lst);
	ptr->next = new;
}

t_plist	*get_to_node(t_plist *node, int ind)
{
	int	i;

	i = 0;
	while (i < ind - 1)
	{
		node = node->next;
		i++;
	}
	return (node);
}
