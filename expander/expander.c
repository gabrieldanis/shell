/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:02 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 18:30:21 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_vars(t_parsed *plist)
{
	t_parsed	*tmp;
	int	sq_flag;
	int	d_flag;
	int	i;

	sq_flag = 0;
	d_flag = 0;
	i =0;
	while (plist->str[i])
	{
		tmp = (t_parsed *) malloc (sizeof(t_parsed));
		if (!tmp)
				free_and_exit(MALLOC_ERROR);
		*tmp = (t_parsed){0};
		plist_add_to_last_ex(&tmp, &plist);
		if (!d_flag)
		{
			while (plist->str[i] && !d_flag)
			{
				if (plist->str[i] == 39)	
				{
					if (!sq_flag)
						sq_flag = 1;
					else
						sq_flag = 0;
				}
				if (plist->str[i] == '$' && !sq_flag)
					d_flag = 1;
				ft_charjoin(&(p_lstlast(plist->ex)->str), plist->str[i]);
				i++;
			}
		}
		else
		{
			while (plist->str[i] && check_is_var(plist->str[i]))	
			{
				d_flag = 0;
				ft_charjoin(&(p_lstlast(plist->ex)->str), plist->str[i]);
				i++;
			}
		}
	}
}

t_parsed *expander(t_parsed *plist)
{
	t_parsed	*start;

	start = plist;
	while (plist)
	{
		if (ft_strchr(plist->str, '$'))
			expand_vars(plist);
		plist = plist->next;
	}
	return (start);
}
