/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:33:38 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/15 14:38:56 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
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
	char	*ch1 = "struct 1";
	char	*ch2 = "struct 2";
	char	*ch3 = "struct 3";
	
	t_list	*l1;
	t_list	*l2;
	t_list	*l3;
	l1 = ft_lstnew(ch1);
	l2 = ft_lstnew(ch2);
	l3 = ft_lstnew(ch3);
	l1->next = l2;
	l2->next = l3;

	printf("first node %s\n", (char *)l1->content);
	printf("should be last node %s\n", (char *)(ft_lstlast(l1)->content));
	
}
*/
