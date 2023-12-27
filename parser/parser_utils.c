/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:40:55 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 14:51:42 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_parsed	*p_lstlast(t_parsed *list)
{
	while (list->next)
		list = list->next;	
	return (list);
}

void	plist_add_to_last(t_parsed **tmp, t_shell *s)
{
	if (!s->lst) 
		s->lst = *tmp;
	else
		p_lstlast(s->lst)->next = *tmp;
}


void	set_q_flag(t_token *list, int *q_flag, char *quotes)
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

void	plist_strjoin(t_shell *s, int *q_flag, char *quotes)
{
	char	*old_str;

	old_str = p_lstlast(s->lst)->str;
	p_lstlast(s->lst)->str = ft_strjoin(p_lstlast(s->lst)->str, s->tlst->str); 
	if (!p_lstlast(s->lst)->str)
		free_and_exit(MALLOC_ERROR, s);
	if (old_str)
		free(old_str);
	set_q_flag(s->tlst, q_flag, quotes);
	s->tlst = (s->tlst)->next;

}

void	print_parsed_list(t_shell *s)
{
	t_parsed	*start;

	start = s->lst;
	while (s->lst)
	{
		printf("type: %s\t:  ", token_type(s->lst->type));
		if (s->lst->str)
			printf("%s", s->lst->str);
		if (s->lst->expand)
			printf(" -> %s", s->lst->expand);
		printf("\n");
		if (s->lst->ex)
		{
			while (s->lst->ex)
			{
				printf("\t\t\t%s\n", s->lst->ex->str);
				s->lst->ex = s->lst->ex->next;
			}
		}
		printf("\n");
		if (s->lst->eof)
			printf("EOF\n");
		s->lst = s->lst->next;
	}
	s->lst = start;
}
