/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:40:55 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 16:29:08 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_parsed	*p_lstlast(t_parsed *list)
{
	while (list->next)
		list = list->next;	
	return (list);
}

void	plist_add_to_last(t_parsed **tmp, t_parsed **plist)
{
	if (!(*plist)) 
		*plist = *tmp;
	else
		p_lstlast(*plist)->next = *tmp;
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

void	plist_strjoin(t_parsed *plist, t_token **list, int *q_flag, char *quotes)
{
	char	*old_str;

	old_str = p_lstlast(plist)->str;
	p_lstlast(plist)->str = ft_strjoin(p_lstlast(plist)->str, (*list)->str); 
	if (old_str)
		free(old_str);
	set_q_flag(*list, q_flag, quotes);
	*list = (*list)->next;

}

void	print_parsed_list(t_parsed *list)
{
	while (list)
	{
		printf("type: %s\t:  ", token_type(list->type));
		if (list->str)
			printf("%s", list->str);
		if (list->expand)
			printf(" -> %s", list->expand);
		printf("\n");
		if (list->ex)
		{
			while (list->ex)
			{
				printf("\t%s\n", list->ex->str);
				list->ex = list->ex->next;
			}
		}
		printf("\n");
		if (list->eof)
			printf("EOF\n");
		list = list->next;
	}
}
