/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:56:02 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/15 08:34:32 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	fill_arglst(t_shell *s, t_parsed *node, int *i)
{
	t_parsed	*subnode;

	subnode = node->lst;
	while (subnode)
	{
		if (subnode->type == CMD || subnode->type == ARG)
		{
			node->arglst[*i] = ft_strdup(subnode->str);
			if (!node->arglst[*i])
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			(*i)++;
		}
		subnode = subnode->next;
	}
}

void	arg_list(t_shell *s)
{
	t_parsed	*node;
	int			i;

	node = s->lst;
	while (node)
	{
		node->arglst = (char **)malloc
			((arglst_size(node) + 1) * sizeof(char *));
		if (!node->arglst)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		i = 0;
		fill_arglst(s, node, &i);
		node->arglst[i] = NULL;
		node = node->next;
	}
}

int	arglst_size(t_parsed *node)
{
	t_parsed	*subnode;
	int			i;

	i = 0;
	subnode = node->lst;
	while (subnode)
	{
		if (subnode->type == CMD || subnode->type == ARG)
			i++;
		subnode = subnode->next;
	}
	return (i);
}
