/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/09 16:46:27 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_shell *s)
{
	int	exitval;

	if (n != 0)
		error_message(n, NULL, NULL, s);
	free_2d_array((void **)s->env);
	free_lsts(s);
	exitval = s->rval;
	free(s);
	exit (exitval);
}

void	free_lsts(t_shell *s)
{
	if (s->tlst)
		free_token_list(s->tlst);
	if (s->lst)
		free_parsed_list(s->lst);
	s->tlst = NULL;
	s->lst = NULL;
	s->cmds = 0;
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
