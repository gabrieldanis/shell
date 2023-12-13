/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:05:23 by gdanis            #+#    #+#             */
/*   Updated: 2023/11/11 12:02:40 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *fresh)
{
	t_list	*swap;

	if (fresh != NULL)
	{
		swap = lst[0];
		lst[0] = fresh;
		fresh->next = swap;
	}
}
/*
t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *) malloc (sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

int	main()
{
	t_list	**list = NULL;
	t_list	*new;
	t_list	*old;
	char	*new_stuff = "this is the new stuff";
	char	*old_stuff = "old as fuck stuff";

	new = ft_lstnew((char *)new_stuff);
	old = ft_lstnew((char *)old_stuff);
	list = &old;
	printf("%s\n", (char *)(list[0]->content));
	ft_lstadd_front(list, new);
	printf("%s\n", (char *)(list[0]->content));
}
*/
