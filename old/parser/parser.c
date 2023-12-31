/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:37:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 21:33:32 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	op_char_node(t_shell *s)	
{
	t_parsed	*tmp;

	tmp = (t_parsed *)malloc(sizeof(t_parsed));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s);
	*tmp = (t_parsed){0};
	tmp->str = ft_strdup(s->tlst->str);
	plist_add_to_last(&tmp, s);
	(s->tlst) = (s->tlst)->next;
}


void	word_node(t_shell *s)	
{
	t_parsed	*tmp;
	int	q_flag;
	char	*quotes;

	quotes = " '\"";
	q_flag = 0;
	tmp = (t_parsed *) malloc (sizeof(t_parsed));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s);
	*tmp = (t_parsed){0};
	plist_add_to_last(&tmp, s);
	while (s->tlst && !delimiter_char(s->tlst->str[0]))
	{
		if (s->tlst && !delimiter_char(s->tlst->str[0]) && !q_flag)
			plist_strjoin(s, &q_flag, quotes);
		while (s->tlst && q_flag)
			plist_strjoin(s, &q_flag, quotes);
		if (!s->tlst && q_flag)
			error_message(QUOTE_ERROR, NULL, NULL);
	}
}

void	parser(t_shell *s)
{
	t_token	*start;

	start = s->tlst;
	while (s->tlst)
	{
		while (s->tlst && s->tlst->str[0] != ' ')
		{
			if (op_char(s->tlst->str[0]))
				op_char_node(s);
			else
				word_node(s);
		}
		if (s->tlst)
			s->tlst = s->tlst->next;
	}
	s->tlst = start;
}
