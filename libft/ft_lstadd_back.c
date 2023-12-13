/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gdanis@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:12:06 by gabriel           #+#    #+#             */
/*   Updated: 2023/12/09 08:57:21 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *fresh)
{
	if (!lst || !fresh)
		return ;
	if (*lst)
		(ft_lstlast(lst[0]))->next = fresh;
	else
		lst[0] = fresh;
}
