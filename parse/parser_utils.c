/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:47:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/05 10:29:08 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
/*
void	printlst(t_shell *s)
{
	t_parsed	*node;
	t_parsed	*subnode;
	int			i;

	i = 0;
	node = s->lst;
	printf("\n\n");
	while (node)
	{
		printf("\t\tNODE %d\n", i);
		printf("++++++++++++++++++++++++++++++++++\n");
		subnode = node->lst;
		while (subnode)
		{
			printf("type: %s str: %s\n", token_type(subnode->type),
				subnode->str);
			subnode = subnode->next;
		}
		printf("++++++++++++++++++++++++++++++++++\n\n");
		i++;
		node = node->next;
	}
	printf("\n");
}
*/

t_parsed	*lstlast(t_parsed *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

char	*token_type(int i)
{
	if (i == RED_IN)
		return ("redirect in   ");
	if (i == RED_OUT)
		return ("redirect out  ");
	if (i == PIPE)
		return ("pipe          ");
	if (i == HEREDOC)
		return ("heredoc       ");
	if (i == RED_APP)
		return ("append std out");
	if (i == HEREDOC_DEL)
		return ("heredoc del   ");
	if (i == CMD)
		return ("command       ");
	if (i == ARG)
		return ("argument      ");
	if (i == FILE_DIR)
		return ("file or dir   ");
	if (i == OUTFILE)
		return ("outfile	   ");
	return ("unknown       ");
}

int	parse_lstiter(t_shell *s, int (*f)(t_parsed *node,
	t_parsed *subnode, t_shell *s))
{
	t_parsed	*node;
	t_parsed	*subnode;

	node = s->lst;
	while (node)
	{
		subnode = node->lst;
		while (subnode)
		{
			if (!f(node, subnode, s))
				return (1);
			subnode = subnode->next;
		}
		node = node->next;
	}
	return (0);
}

void	appln_chararr(t_parsed *lst, char *str, t_shell *s)
{
	char	**tmp;
	int		i;

	i = 0;
	while (lst->outfiles && lst->outfiles[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	i = 0;
	while (lst->outfiles && lst->outfiles[i])
	{
		tmp[i] = lst->outfiles[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	if (!tmp[i])
		free_tmp_exit(tmp, s);
	i++;
	tmp[i] = NULL;
	if (lst->outfiles)
		free(lst->outfiles);
	lst->outfiles = tmp;
}

void	free_tmp_exit(char **tmp, t_shell *s)
{
	free(tmp);
	free_and_exit(MALLOC_ERROR, s, NULL, NULL);
}
