/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/31 15:23:01 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_parsed	*lstlast(t_parsed *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	addnewlstback(t_shell *s, t_parsed *lst)
{
	t_parsed	*tmp;

	tmp = (t_parsed *)malloc(sizeof(t_parsed));
	*tmp = (t_parsed){0};
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s);
	if (!lst)
	{
		if (!s->lst)
			s->lst = tmp;
		else
			lstlast(s->lst)->next = tmp;
	
	}
	else
	{
		if (!lst->lst)
			lst->lst = tmp;
		else
			lstlast(lst->lst)->next = tmp;
	}
}

void	init_plst(t_shell *s)
{
	t_token	*start;
	t_token	*ex_start;
	
	start = s->tlst;
	while (s->tlst)
	{
		if (s->tlst->ex->str)
			addnewlstback(s, NULL);
		while (s->tlst && s->tlst->type != PIPE)
		{
			ex_start = s->tlst->ex;
			while (s->tlst->ex)	
			{
				if (s->tlst->ex->str)
				{
					addnewlstback(s, lstlast(s->lst));
					lstlast(lstlast(s->lst)->lst)->str = s->tlst->ex->str;
				}
				s->tlst->ex = s->tlst->ex->next;
			}
			s->tlst->ex = ex_start;
			s->tlst = s->tlst->next;
		}
		if (s->tlst && s->tlst->type == PIPE)
		{
			addnewlstback(s, lstlast(s->lst));
			lstlast(lstlast(s->lst)->lst)->str = s->tlst->str;
			s->tlst = s->tlst->next;
		}
	}
	s->tlst = start;
}

void	printlst(t_shell *s)
{
	t_parsed	*start;
	t_parsed	*sub_start;
	int		i;
	
	i = 0;
	start = s->lst;
	while (s->lst)
	{
		printf("\n\n\tNODE %d\n", i);
		printf("+++++++++++++++++++++++++\n");
		sub_start = s->lst->lst;
		while (s->lst->lst)	
		{
			printf("type: %d, %s\n", s->lst->lst->type, s->lst->lst->str);
			s->lst->lst = s->lst->lst->next;
		}
		printf("+++++++++++++++++++++++++\n\n");
		i++;
		s->lst->lst = sub_start;
		s->lst = s->lst->next;
	}
	s->lst = start;
}
