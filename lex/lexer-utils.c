/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:52:50 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 11:31:30 by gdanis           ###   ########.fr       */
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

void	token_addlstlast(t_token **lst)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	if (!(*lst))
		*lst = tmp;
	else
		last_token(*lst)->next = tmp;
}

void	print_token(t_shell *s)
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
		if (s->tlst->sp)
		{
			printf("-------------------------------\n");
			printf("split:");
			sp_start = s->tlst->sp;
			while (s->tlst->sp)
			{
				if (s->tlst->sp->str[0] == '\0')
					printf("string with only null terminator");
				printf("\t\t%s\n", s->tlst->sp->str);
				s->tlst->sp = s->tlst->sp->next;
			}
			s->tlst->sp = sp_start;
		}
		if (s->tlst->ex)
		{
			printf("-------------------------------\n");
			printf("exp:");
			ex_start = s->tlst->ex;
			while (s->tlst->ex)
			{
				if (s->tlst->ex->str && s->tlst->ex->str[0] == '\0')
					printf("string with only null terminator");
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
