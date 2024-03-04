/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/04 11:00:35 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_and_exit(int n, t_shell *s, char *exe_name, char *str)
{
	int	exitval;

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
	clear_history();
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
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		if (tmp->cmd)
			free (tmp->cmd);
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

void	free_2d_array_i(void ***arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free((*arr)[j++]);
	free(*arr);
	*arr = NULL;
}

void	delete_files(t_shell *s)
{
	t_parsed	*node;

	node = s->lst->lst;
	while(node)
	{
		if (node->type == HEREDOC)
		{
			if (unlink(node->filename) == -1) 
				free_and_exit(UNLINK_ERROR, s, NULL, NULL);
		}
		node = node->next;
	}
}
