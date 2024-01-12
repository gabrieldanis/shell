/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:47:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/10 18:26:16 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	printlst(t_shell *s)
{
	t_parsed	*start;
	t_parsed	*sub_start;
	int		i;
	
	i = 0;
	start = s->lst;
	printf("\n\n");
	while (s->lst)
	{
		printf("\t\tNODE %d\n", i);
		printf("++++++++++++++++++++++++++++++++++\n");
		sub_start = s->lst->lst;
		while (s->lst->lst)	
		{
			printf("type: %s str: %s\n", token_type(s->lst->lst->type), s->lst->lst->str);
			s->lst->lst = s->lst->lst->next;
		}
		printf("++++++++++++++++++++++++++++++++++\n\n");
		i++;
		s->lst->lst = sub_start;
		s->lst = s->lst->next;
	}
	printf("\n");
	s->lst = start;
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
	return ("unknown       ");
}

void	parse_lstiter(t_shell *s, int (*f)(t_parsed *lst, t_shell *s))
{
	t_parsed	*start;
	t_parsed	*sub_start;
	
	start = s->lst;
	while (s->lst)
	{
		sub_start = s->lst->lst;
		while (s->lst->lst)	
		{
			if (!f(s->lst->lst, s))
				return ;
			s->lst->lst = s->lst->lst->next;
		}
		s->lst->lst = sub_start;
		s->lst = s->lst->next;
	}
	s->lst = start;
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
		free_and_exit(MALLOC_ERROR, s);
	i = 0;
	while (lst->outfiles && lst->outfiles[i])
	{
		tmp[i] = lst->outfiles[i];
		i++;
	}
	tmp[i] = str;
	i++;
	tmp[i] = NULL;
	if (lst->outfiles)
		free(lst->outfiles);
	lst->outfiles = tmp;
}








