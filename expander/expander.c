/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:02 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/20 10:29:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_sublist_var (t_parsed *plist, int *i)
{
			while (plist->str[*i])	
			{
				ft_charjoin(&(p_lstlast(plist->ex)->str), plist->str[*i]);
				(*i)++;
				if (!check_is_var(plist->str[*i]))
					break ;
			}
}

void	expand_sublist_nonvar(t_parsed *plist, int *i, int *sq_flag)
{
	while (plist->str[*i])
	{
		if (plist->str[*i] == '$' && !(*sq_flag))
			break ;
		set_sq_flag(sq_flag, plist->str[*i]);
		ft_charjoin(&(p_lstlast(plist->ex)->str), plist->str[*i]);
		(*i)++;
	}
}

void	expand_sublist(t_parsed *plist)
{
	t_parsed	*tmp;
	int	sq_flag;
	int	i;

	sq_flag = 0;
	i =0;
	while (plist->str[i])
	{
		tmp = (t_parsed *) malloc (sizeof(t_parsed));
		if (!tmp)
				free_and_exit(MALLOC_ERROR);
		*tmp = (t_parsed){0};
		plist_add_to_last_ex(&tmp, &plist);
		if (plist->str[i] != '$')
			expand_sublist_nonvar(plist, &i, &sq_flag);
		else
			expand_sublist_var(plist, &i);
	}
}

void	strjoin_expanded_str(t_parsed *plist)
{
	int	q_flag;
	char	*quotes;
	char	*tmp;
	int	i;
	t_parsed	*start;

	quotes = " '\"";
	q_flag = 0;
	i = 0;
	start = plist->ex;
	while (plist->ex)
	{
		if (plist->ex->str[0] == '$' && q_flag != 1
			&& ft_strlen(plist->ex->str) != 1)
		{
			tmp = plist->expand;	
			plist->expand = ft_strjoin(plist->expand, getenv(plist->ex->str + 1));
			if (tmp)
				free(tmp);
		}
		else
		{
			i = 0;
			while (plist->ex->str[i])	
			{
				set_q_flag_ex(plist->ex, &q_flag, quotes, &i);
				if (plist->ex->str[i])
				{
					ft_charjoin(&plist->expand, plist->ex->str[i]);
					i++;
				}
			}
		}
		plist->ex = plist->ex->next;
	}
	plist->ex = start;
}

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
		if (plist->str[i])
		{
			ft_charjoin(&tmp, plist->str[i]);
			i++;
		}
	}
	free(plist->str);
	plist->str = tmp;
}

t_parsed *expander(t_parsed *plist)
{
	t_parsed	*start;

	start = plist;
	while (plist)
	{
		if (ft_strchr(plist->str, '$'))
			expand_sublist(plist);
		if (plist->ex)
			strjoin_expanded_str(plist);
		remove_quotes(plist);
		plist = plist->next;
	}
	return (start);
}
