/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:52:50 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/29 19:32:35 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*last_token(t_token *t)
{
	while(t && t->next)
		t = t->next;	
	return (t);
}

void	setqflag(int *flag, char c)
{
	if (!(*flag) && (c == '"' || c == 39))
	{
		if (c == '"')	
			*flag = 2;
		if (c == 39)
			*flag = 1;
	}
	else if((*flag == 2 && c == '"') || (*flag == 1 && c == 39))
		*flag = 0;
}

void	token_addlstlast(t_token **lst, t_token *tmp)
{
	if (!(*lst))
		*lst = tmp;
	else
		last_token(*lst)->next = tmp;
}

void	print_tokens(t_shell *s)
{
	t_token	*start;
	t_token	*sp_start;
	t_token	*ex_start;

	start = s->tlst;
	while (s->tlst)
	{
		printf("===============================\n");
		printf("type: %d:\t", s->tlst->type);
		if (s->tlst->str)
			printf("%s", s->tlst->str);
		printf("\n");
		printf("-------------------------------\n");
		printf("split:");
		if (s->tlst->sp)
		{
			sp_start = s->tlst->sp;
			while (s->tlst->sp)
			{
				printf("\t\t%s\n", s->tlst->sp->str);
				s->tlst->sp = s->tlst->sp->next;
			}
			s->tlst->sp = sp_start;
		}
		printf("-------------------------------\n");
		printf("exp:");
		if (s->tlst->ex)
		{
			ex_start = s->tlst->ex;
			while (s->tlst->ex)
			{
				printf("\t\t%s\n", s->tlst->ex->str);
				s->tlst->ex = s->tlst->ex->next;
			}
			s->tlst->ex = ex_start;
		}
		printf("\n");
		s->tlst = s->tlst->next;
	}
	s->tlst = start;
}
