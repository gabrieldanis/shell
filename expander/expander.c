/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:04:02 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 22:12:57 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_sublist_var (t_shell *s, int *i)
{
	while (s->lst->str[*i])	
	{
		ft_charjoin(&(p_lstlast(s->lst->ex)->str), s->lst->str[*i], s);
		(*i)++;
		if (!check_is_var(s->lst->str[*i]))
			break ;
	}
}

void	expand_sublist_nonvar(t_shell *s, int *i)
{
	char	*quotes;
	int	q_flag;

	quotes = " '\"";
	q_flag = 0;
	while (s->lst->str[*i])
	{
		if (s->lst->str[*i] == '$' && q_flag != 1)
			break ;
		set_q_flag_plist(s->lst, &q_flag, quotes);
		ft_charjoin(&(p_lstlast(s->lst->ex)->str), s->lst->str[*i], s);
		(*i)++;
	}
}

void	expand_sublist(t_shell *s)
{
	t_parsed	*tmp;
	int	i;

	i = 0;
	while (s->lst->str[i])
	{
		tmp = (t_parsed *) malloc (sizeof(t_parsed));
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s);
		*tmp = (t_parsed){0};
		plist_add_to_last_ex(&tmp, s);
		if (s->lst->str[i] != '$')
			expand_sublist_nonvar(s, &i);
		else
			expand_sublist_var(s, &i);
	}
}

void	strjoin_expanded_str(t_shell *s)
{
	int	q_flag;
	char	*quotes;
	char	*tmp;
	int	i;
	t_parsed	*start;

	quotes = " '\"";
	q_flag = 0;
	i = 0;
	start = s->lst->ex;
	while (s->lst->ex)
	{
		if (s->lst->ex->str[0] == '$' && q_flag != 1
			&& ft_strlen(s->lst->ex->str) != 1)
		{
			tmp = s->lst->expand;	
			s->lst->expand = ft_strjoin(s->lst->expand, ft_getenv(s->lst->ex->str + 1, s));
			if (!s->lst->expand)
				free_and_exit(MALLOC_ERROR, s);
			if (tmp)
				free(tmp);
		}
		else
		{
			i = 0;
			while (s->lst->ex->str[i])	
			{
				set_q_flag_ex(s->lst->ex, &q_flag, quotes, &i);
				if (s->lst->ex->str[i] && s->lst->ex->str[i] != quotes[q_flag])
				{
					ft_charjoin(&s->lst->expand, s->lst->ex->str[i], s);
					i++;
				}
			}
		}
		s->lst->ex = s->lst->ex->next;
	}
	s->lst->ex = start;
}

void	expander(t_shell *s)
{
	t_parsed	*start;

	start = s->lst;
	while (s->lst)
	{
		if (ft_strchr(s->lst->str, '$'))
			expand_sublist(s);
		if (s->lst->ex)
			strjoin_expanded_str(s);
		if (ft_strchr(s->lst->str, '"') || ft_strchr(s->lst->str, 39))
			remove_quotes(s);
		if (s->lst->expand)	 
			s->lst->fstr = s->lst->expand;
		else
			s->lst->fstr = s->lst->str;
		s->lst = s->lst->next;
	}
	s->lst = start;
}
