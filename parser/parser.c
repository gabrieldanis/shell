/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:37:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/21 19:42:01 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_parsed	*op_char_node(t_token **list, t_parsed *plist)	
{
	t_parsed	*tmp;

	tmp = (t_parsed *)malloc(sizeof(t_parsed));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	*tmp = (t_parsed){0};
	tmp->str = ft_strdup((*list)->str);
	plist_add_to_last(&tmp, &plist);
	(*list) = (*list)->next;
	return (plist);
}


t_parsed	*word_node(t_token **list, t_parsed *plist)	
{
	t_parsed	*tmp;
	int	q_flag;
	char	*quotes;

	quotes = " '\"";
	q_flag = 0;
	tmp = (t_parsed *) malloc (sizeof(t_parsed));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	*tmp = (t_parsed){0};
	plist_add_to_last(&tmp, &plist);
	while (*list && !delimiter_char((*list)->str[0]))
	{
		if (*list && !delimiter_char((*list)->str[0]) && !q_flag)
			plist_strjoin(plist, list, &q_flag, quotes);
		while (*list && q_flag)
			plist_strjoin(plist, list, &q_flag, quotes);
		if (!(*list) && q_flag)
			free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	}
	return (plist);
}

t_parsed	*parser(t_token *list)
{
	t_parsed *plist;

	plist = NULL;
	while (list)
	{
		while (list && list->str[0] != ' ')
		{
			if (op_char(list->str[0]))
					plist = op_char_node(&list, plist);
			else
					plist = word_node(&list, plist);
		}
		if (list)
			list = list->next;
	}
	return (plist);
}

