/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:10:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/09 11:44:55 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	arg_list(t_shell *s)
{
	t_parsed	*start;
	t_parsed	*sub_start;
	int		i;

	start = s->lst;
	while (s->lst && s->lst->lst)
	{
		s->lst->arglst = (char **)malloc((arglst_size(s->lst) + 1) * sizeof(char *));
		if (!s->lst->arglst)
			free_and_exit(MALLOC_ERROR, s);
		sub_start = s->lst->lst;
		i = 0;
		while (s->lst->lst)
		{
			if (s->lst->lst->type == CMD || s->lst->lst->type == ARG)
			{
				s->lst->arglst[i] = ft_strdup(s->lst->lst->str);
				if (!s->lst->arglst[i])
					free_and_exit(MALLOC_ERROR, s);
				i++;
			}
			s->lst->lst = s->lst->lst->next;
		}
		s->lst->arglst[i] = NULL;
		s->lst->lst = sub_start;
		s->lst = s->lst->next;
	}
	s->lst = start;
}

void	exit_child(int n, t_shell *s)
{
	error_message(n, NULL, NULL, s);
	exit(0);
}
