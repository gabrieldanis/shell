/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/07 19:58:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_shell *s, char *exe_name, char *str)
{
	int	exitval;

	fd_closer(s);
	free_s_str(s);
	if (s->cwd)
		free(s->cwd);
	if (s->var)
		free(s->var);
	if (n != 0)
		s->rval = error_message(n, exe_name, str, s);
	if (s && s->env)
		free_2d_array((void **)s->env);
	free_lsts(s);
	if (s)
	{
		exitval = s->rval;
		free(s);
	}
	else
		exitval = MALLOC_ERROR;
	rl_clear_history();
	exit (exitval);
}

void	free_pipes(t_shell *s)
{
	int	i;

	i = 0;
	if (s->pipes && s->pipes[0])
	{
		while (i < s->cmds - 1)
		{
			free (s->pipes[i]);
			i++;
		}
	}
	free (s->pipes);
	s->pipes = NULL;
}

void	free_lsts(t_shell *s)
{
	if (s)
	{
		if (s->tlst)
			free_token_list(s->tlst);
		if (s->lst)
			free_parsed_list(s->lst);
		s->tlst = NULL;
		s->lst = NULL;
		free_pipes(s);
	}
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
		free_parsed_list_strings(tmp);
		if (tmp->outfiles)
		{
			free_2d_array((void **)tmp->outfiles);
			tmp->outfiles = NULL;
		}
		if (tmp->arglst)
		{
			free_2d_array((void **)tmp->arglst);
			tmp->arglst = NULL;
		}
		if (tmp->lst)
		{
			free_parsed_list(tmp->lst);
			tmp->lst = NULL;
		}
		free(tmp);
	}
}
