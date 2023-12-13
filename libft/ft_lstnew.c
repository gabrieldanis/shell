/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:34:08 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/15 10:39:04 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
/*
int	main()
{
	t_list	*test;
	char	*ch = "I am stupid.";

	test = ft_lstnew((char *)ch);

	printf("is this x? %s\n", ch);
	printf("is this x? %s\n", (char *)(test->content));
	if (test->next == NULL)
		printf("success\n");
	free (test);
}
*/
