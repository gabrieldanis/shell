/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/15 12:16:22 by dberes           ###   ########.fr       */
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
	if (!tmp)
	{
		if (s->ex_start && s->tlst->ex)
			s->tlst->ex = s->ex_start;
		if (s->t_start && s->tlst)
			s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s);
	}
	*tmp = (t_parsed){0};
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
	s->t_start = s->tlst;
	while (s->tlst)
	{
		addnewlstback(s, NULL);
		while (s->tlst && s->tlst->type != PIPE)
		{
			s->ex_start = s->tlst->ex;
			while (s->tlst->ex)	
			{
				if (s->tlst->ex->str)
				{
					addnewlstback(s, lstlast(s->lst));
					node_dup(lstlast(lstlast(s->lst)->lst), s->tlst->ex->str, s);
				}
				s->tlst->ex = s->tlst->ex->next;
			}
			s->tlst->ex = s->ex_start;
			s->tlst = s->tlst->next;
		}
		if (s->tlst && s->tlst->type == PIPE)
		{
			addnewlstback(s, lstlast(s->lst));
			node_dup(lstlast(lstlast(s->lst)->lst), s->tlst->str, s);
			s->tlst = s->tlst->next;
		}
	}
	s->tlst = s->t_start;
}

void	node_dup(t_parsed *lst, char *s2, t_shell *s)
{
	lst->str = ft_strdup(s2);
	if (!lst->str)
	{
		if (s->ex_start && s->tlst->ex)
			s->tlst->ex = s->ex_start;
		if (s->t_start && s->tlst)
			s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s);
	}
	lst->type = s->tlst->type;

}

int	parse_isfile(t_parsed *lst, t_shell *s)
{
	if ((lst->type == RED_IN || lst->type == RED_OUT 
		||lst->type == RED_APP) && lst->next)
	{
		if (lst->next->type)
		{
			error_message(UNEX_TOKEN, NULL, lst->next->str, s);
			return (0);
		}
	}
	if (lst->type == RED_IN && lst->next && !lst->next->type)
	{
		lst->next->type = INFILE;
		s->lst->infile = lst->next->str;
	}
	if ((lst->type == RED_OUT || lst->type == RED_APP) && lst->next
			&& !lst->next->type)
	{
		lst->next->type = OUTFILE;
		appln_chararr(s->lst, lst->next->str, s);
		if (lst->type == RED_OUT)
			s->lst->append = 0;
		else
			s->lst->append = 1;
	}
	return (1);
}

int	parse_cmdargs(t_parsed *lst, t_shell *s)
{
	static int	cmd;

	(void)s;
	if (!lst->type && !cmd)
	{
		lst->type = CMD;
		cmd = 1;
	}
	if (!lst->type && cmd)
		lst->type = ARG;
	if (!lst->next)
		cmd = 0;
	return (1);
}
