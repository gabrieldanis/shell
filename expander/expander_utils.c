/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:56:51 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 16:43:46 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	plist_add_to_last_ex(t_parsed **tmp, t_parsed **plist)
{
	if (!((*plist)->ex)) 
		(*plist)->ex = *tmp;
	else
		p_lstlast((*plist)->ex)->next = *tmp;
}

int	check_is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

