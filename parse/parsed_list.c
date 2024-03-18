/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:16:30 by dberes            #+#    #+#             */
/*   Updated: 2024/03/16 14:34:03 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	addnewlstback(t_shell *s, t_parsed *lst)
{
	t_parsed	*tmp;

	tmp = (t_parsed *)malloc(sizeof(t_parsed));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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

void	add_pipe_node(t_shell *s, t_token **t_node)
{
	if (*t_node && (*t_node)->type == PIPE)
	{
		addnewlstback(s, lstlast(s->lst));
		node_dup(lstlast(lstlast(s->lst)->lst), *t_node, (*t_node)->str, s);
		*t_node = (*t_node)->next;
	}
}

void	add_regular_node(t_shell *s, t_token *t_node, t_token *ex_node)
{
	addnewlstback(s, lstlast(s->lst));
	node_dup(lstlast(lstlast(s->lst)->lst),
		t_node, ex_node->str, s);
	lstlast(lstlast(s->lst)->lst)->heredoc_quote
	= t_node->heredoc_quote;
}

void	init_plst(t_shell *s)
{
	t_token	*t_node;
	t_token	*ex_node;

	t_node = s->tlst;
	while (t_node)
	{
		addnewlstback(s, NULL);
		while (t_node && t_node->type != PIPE)
		{
			ex_node = t_node->ex;
			while (ex_node)
			{
				if (ex_node->str)
					add_regular_node(s, t_node, ex_node);
				ex_node = ex_node->next;
			}
			t_node = t_node->next;
		}
		add_pipe_node(s, &t_node);
	}
}

void	node_dup(t_parsed *node, t_token *t_node, char *s2, t_shell *s)
{
	node->str = ft_strdup(s2);
	if (!node->str)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	node->type = t_node->type;
}
