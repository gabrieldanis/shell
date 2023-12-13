/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gdanis@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:43:07 by gabriel           #+#    #+#             */
/*   Updated: 2023/11/11 12:02:09 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		(*del)(lst->content);
		free((t_list *)lst);
	}
}
/*
int	main(void)
{
	t_list	*one;
	char	*ch;
	char	*str = "hello";

	ch = (char *) malloc (sizeof(char) * 6);
	ft_strlcpy(ch, str, 6);
	printf("this is result of copy function %s", ch);
	one = ft_lstnew((char *)ch);
	ft_lstdelone(one, free);
}
*/
