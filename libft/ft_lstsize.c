/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:57 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/15 14:36:57 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (lst != NULL)
	{
		i++;
		while (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
	}
	return (i);
}
/*
int	main()
{
	char	*ch1 = "struct 1";
	char	*ch2 = "struct 2";
	char	*ch3 = "struct 3";
	t_list	*l1;
	t_list	*l2;
	t_list	*l3;
	t_list	*test;

	test = ft_lstnew(ch3);

	l1 = ft_lstnew(ch1);
	l2 = ft_lstnew(ch2);
	l3 = ft_lstnew(ch3);
	l1->next = l2;
	l2->next = l3;
	test = l1->next;

	printf("before %s\n", (char *)l1->content);
	printf("list length %d\n", ft_lstsize(l1));
	printf("check %s\n", (char *)l1->content);
	
}
*/
