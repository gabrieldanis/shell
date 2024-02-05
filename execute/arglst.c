/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:56:02 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/05 13:35:14 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	fill_arglst(t_shell *s, int *i)
{
	if (s->lst->lst->type == CMD || s->lst->lst->type == ARG)
	{
		s->lst->arglst[*i] = ft_strdup(s->lst->lst->str);
		if (!s->lst->arglst[*i])
		{
			s->lst->lst = s->pp_start;
			s->lst = s->p_start;
			free_and_exit(MALLOC_ERROR, s);
		}
		(*i)++;
	}
	s->lst->lst = s->lst->lst->next;
}

void	arg_list(t_shell *s)
{
	int		i;

	s->p_start = s->lst;
	while (s->lst && s->lst->lst)
	{
		s->lst->arglst = (char **)malloc
			((arglst_size(s->lst) + 1) * sizeof(char *));
		if (!s->lst->arglst)
			free_and_exit(MALLOC_ERROR, s);
		s->pp_start = s->lst->lst;
		i = 0;
		while (s->lst->lst)
			fill_arglst(s, &i);
		s->lst->arglst[i] = NULL;
		s->lst->lst = s->pp_start;
		s->lst = s->lst->next;
	}
	s->lst = s->p_start;
}

int	arglst_size(t_parsed *lst)
{
	t_parsed	*sub_start;
	int			i;

	i = 0;
	sub_start = lst->lst;
	while (lst->lst)
	{
		if (lst->lst->type == CMD || lst->lst->type == ARG)
			i++;
		lst->lst = lst->lst->next;
	}
	lst->lst = sub_start;
	return (i);
}
