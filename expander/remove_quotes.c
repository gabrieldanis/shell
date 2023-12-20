/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:11:11 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/20 16:04:53 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	remove_quotes(t_parsed *plist)
{
	char	*quotes;
	char	*tmp;
	int	q_flag;
	int	i;

	quotes = " '\"";
	q_flag = 0;
	tmp = NULL;
	i = 0;
	while (plist->str[i])	
	{
		set_q_flag_ex(plist, &q_flag, quotes, &i);
		if (plist->str[i] && plist->str[i] != quotes[q_flag])
		{
			ft_charjoin(&tmp, plist->str[i]);
			i++;
		}
	}
	if (!tmp)
		tmp = ft_strdup("");
	free(plist->str);
	plist->str = tmp;
}

void	set_q_flag_plist(t_parsed *list, int *q_flag, char *quotes)
{
	if (list && !*q_flag)
	{
		if (list->str[0] == 39)
				*q_flag = 1;
		if (list->str[0] == '"')
				*q_flag = 2;
	}
	else if (list && *q_flag && list->str[0] == quotes[*q_flag])
		*q_flag = 0;
}
