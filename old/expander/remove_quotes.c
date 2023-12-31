/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:11:11 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 15:30:56 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	remove_quotes(t_shell *s)
{
	char	*quotes;
	char	*tmp;
	int	q_flag;
	int	i;

	quotes = " '\"";
	q_flag = 0;
	tmp = NULL;
	i = 0;
	while (s->lst->str[i])	
	{
		set_q_flag_ex(s->lst, &q_flag, quotes, &i);
		if (s->lst->str[i] && s->lst->str[i] != quotes[q_flag])
		{
			ft_charjoin(&tmp, s->lst->str[i], s);
			i++;
		}
	}
	if (!tmp)
		tmp = ft_strdup("");
	free(s->lst->str);
	s->lst->str = tmp;
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
