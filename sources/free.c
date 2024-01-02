/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 07:26:37 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_shell *shell)
{
	(void)shell;
	if (n != 0)
		error_message(n, NULL, NULL);
	/*
	 * great code that frees everything
	 * goes here :
	if (shell->arglst)
		free_2d_array((void **)shell->arglst);
	if (shell->tlst)
		free_token_list(shell);
	if (shell->lst)
		free_parsed_list(shell->lst);
	if (shell->env)
		free_2d_array((void **)shell->env);
	 */
	if (n == 0)
		printf("exit\n");
	exit (n);
}


void	free_token_list(t_shell *s)
{
	t_token	*tmp;

	while (s->tlst)
	{
		tmp = s->tlst;
		s->tlst = s->tlst->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	s->tlst = NULL;
}

/*
void	free_parsed_list(t_parsed *list)
{
	t_parsed	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp->ex)
			free_parsed_list(tmp->ex);
		free(tmp);
	}
}
*/
void	free_2d_array(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			if (ptr[i])
				free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}
