/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 15:44:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_shell *s)
{
	int	i;
	(void)s;
	if (n != 0)
		error_message(n, NULL, NULL);
	free_lsts(s);
	i = 0;
	free_2d_array((void **)s->env);
	s->env = NULL;
	free (s);
	if (n == 0)
		printf("exit\n");
	exit (n);
}

void	free_lsts(t_shell *s)
{
	if (s->tlst)
		free_token_list(s->tlst);
	if (s->lst)
		free_parsed_list(s->lst);
	s->tlst = NULL;
	s->lst = NULL;
}

void	free_token_list(t_token *tlst)
{
	t_token	*tmp;

	while (tlst)
	{
		tmp = tlst;
		tlst = tlst->next;
		if (tmp->sp)
		{
			free_token_list(tmp->sp);
			tmp->sp = NULL;
		}
		if (tmp->ex)
		{
			free_token_list(tmp->ex);
			tmp->ex = NULL;
		}
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
	}
}

void	free_parsed_list(t_parsed *lst)
{
	t_parsed	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		if (tmp->arglst)
			free_2d_array((void **)tmp->arglst);
		if (tmp->lst)
		{
			free_parsed_list(tmp->lst);
			tmp->lst = NULL;
		}
		free(tmp);
	}
}

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
