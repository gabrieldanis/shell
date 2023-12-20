/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:56:51 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/20 09:57:43 by gdanis           ###   ########.fr       */
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

void	set_q_flag_ex(t_parsed *list, int *q_flag, char *quotes, int *i)
{
	if (list && *q_flag && list->str[*i] == quotes[*q_flag])
	{
		*q_flag = 0;
		(*i)++;
	}
	if (list && !*q_flag)
	{
		if (list->str[*i] == 39)
		{
				*q_flag = 1;
				(*i)++;
		}
		else if (list->str[*i] == '"')
		{
				*q_flag = 2;
				(*i)++;
		}
	}
}

void	set_sq_flag(int *sq_flag, char c)
{
	if (c == 39)	
	{
		if (!(*sq_flag))
			*sq_flag = 1;
		else
			*sq_flag = 0;
	}
}

