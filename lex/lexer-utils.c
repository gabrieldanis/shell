/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:52:50 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/15 17:00:33 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*last_token(t_token *t)
{
	while (t && t->next)
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
	else if ((*flag == 2 && c == '"') || (*flag == 1 && c == 39))
		*flag = 0;
}

void	token_addlstlast(t_token **lst, t_shell *s)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	*tmp = (t_token){0};
	if (!(*lst))
		*lst = tmp;
	else
		last_token(*lst)->next = tmp;
}

/*
void	print_token(t_shell *s)
{
	t_token	*node;
	t_token	*sp_node;
	t_token	*ex_node;

	node = s->tlst;
	while (node)
	{
		sp_node = node->sp;
		ex_node = node->ex;
		printf("===============================\n");
		printf("type: %d:\t", node->type);
		if (node->str)
			printf("%s", node->str);
		printf("\n");
		if (sp_node)
		{
			printf("-------------------------------\n");
			printf("split:");
			while (sp_node)
			{
				if (sp_node->str[0] == '\0')
					printf("\t\t\\0");
				printf("\t\t%s\n", sp_node->str);
				sp_node = sp_node->next;
			}
		}
		if (ex_node)
		{
			printf("-------------------------------\n");
			printf("exp:");
			while (ex_node)
			{
				if (ex_node->str && ex_node->str[0] == '\0')
					printf("\t\t\\0");
				printf("\t\t%s\n", ex_node->str);
				ex_node = ex_node->next;
			}
		}
		printf("\n");
		node = node->next;
	}
}
*/

int	is_delimiter(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
