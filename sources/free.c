/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/21 19:43:28 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_token *list, t_parsed *plist, char **envp)
{
	if (n != 0)
		error_message(n, NULL, NULL);
	/*
	 * great code that frees everything
	 * goes here :
	 */
	if (list)
		free_token_list(list);
	if (plist)
		free_parsed_list(plist);
	if (envp)
		free_2d_array((void **)envp);
	if (n == 0)
		printf("exit\n");
	exit (n);
}

void	free_token_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_parsed_list(t_parsed *list)
{
	t_parsed	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp->expand)
			free(tmp->expand);
		if (tmp->ex)
			free_parsed_list(tmp->ex);
		free(tmp);
	}
}
