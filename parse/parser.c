/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/09 16:28:09 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_parsed	*lstlast(t_parsed *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	addnewlstback(t_shell *s, t_parsed *lst)
{
	t_parsed	*tmp;

	tmp = (t_parsed *)malloc(sizeof(t_parsed));
	if (!tmp)
	{
		if (s->ex_start && s->tlst->ex)
			s->tlst->ex = s->ex_start;
		if (s->t_start && s->tlst)
			s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	*tmp = (t_parsed){0};
	if (!lst)
	{
		if (!s->lst)
			s->lst = tmp;
		else
			lstlast(s->lst)->next = tmp;
	}
	else
	{
		if (!lst->lst)
			lst->lst = tmp;
		else
			lstlast(lst->lst)->next = tmp;
	}
}

void	init_plst(t_shell *s)
{
	s->t_start = s->tlst;
	while (s->tlst)
	{
		addnewlstback(s, NULL);
		while (s->tlst && s->tlst->type != PIPE)
		{
			s->ex_start = s->tlst->ex;
			while (s->tlst->ex)	
			{
				if (s->tlst->ex->str)
				{
					addnewlstback(s, lstlast(s->lst));
					node_dup(lstlast(lstlast(s->lst)->lst), s->tlst->ex->str, s);
				}
				s->tlst->ex = s->tlst->ex->next;
			}
			s->tlst->ex = s->ex_start;
			s->tlst = s->tlst->next;
		}
		if (s->tlst && s->tlst->type == PIPE)
		{
			addnewlstback(s, lstlast(s->lst));
			node_dup(lstlast(lstlast(s->lst)->lst), s->tlst->str, s);
			s->tlst = s->tlst->next;
		}
	}
	s->tlst = s->t_start;
}

void	node_dup(t_parsed *lst, char *s2, t_shell *s)
{
	lst->str = ft_strdup(s2);
	if (!lst->str)
	{
		if (s->ex_start && s->tlst->ex)
			s->tlst->ex = s->ex_start;
		if (s->t_start && s->tlst)
			s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	lst->type = s->tlst->type;

}

int	parse_isfile(t_parsed *lst, t_shell *s)
{
	if ((lst->type == RED_IN || lst->type == RED_OUT 
		||lst->type == RED_APP) && lst->next)
	{
		if (lst->next->type)
		{
			error_message(UNEX_TOKEN, NULL, lst->next->str, s);
			return (0);
		}
	}
	if (lst->type == RED_IN && lst->next && !lst->next->type)
	{
		lst->next->type = INFILE;
		s->lst->infile = lst->next->str;
	}
	if ((lst->type == RED_OUT || lst->type == RED_APP) && lst->next
			&& !lst->next->type)
	{
		lst->next->type = OUTFILE;
		appln_chararr(s->lst, lst->next->str, s);
		if (lst->type == RED_OUT)
			s->lst->append = 0;
		else
			s->lst->append = 1;
	}
	return (1);
}

int	parse_cmdargs(t_parsed *lst, t_shell *s)
{
	static int	cmd;

	(void)s;
	if (!lst->type && !cmd)
	{
		lst->type = CMD;
		cmd = 1;
	}
	if (!lst->type && cmd)
		lst->type = ARG;
	if (!lst->next)
		cmd = 0;
	return (1);
}

int	parse_heredoc(t_parsed *lst, t_shell *s)
{
	char		*line;
	char		*line_new;
	t_parsed	*node;
	
	node = lst;
	line = NULL;
	//while(node)
	//{
	if (node->type == HEREDOC)
	{
		//node->infile = 1;
		create_tmp_file(node, s);
		printf("%s\n", node->filename);
		s->heredocfd = open(node->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (s->heredocfd == -1) 
		{
    		perror("Error opening file");
    		free_and_exit(OPEN_ERROR, s, NULL, NULL);
		}
		while (1)
		{
			line = readline("> ");
			if (!ft_strncmp(line, node->next->str, ft_strlen(line) +1))
				break ;
			line_new = ft_strjoin(line, "\n");
			if(!line_new)
			{
				free(line);
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			}
			if(write(s->heredocfd, line_new, ft_strlen(line_new)) == -1)
				free_and_exit(WRITE_ERROR, s, NULL, NULL);
		}
		free(line_new);
	}
	//node = node->next;
	//}
	return (1);
}

void	create_tmp_file(t_parsed *node, t_shell *s)
{
	int			i;
	const char	*charset;
	
	i = 0;
	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	node->filename = (char *)malloc(sizeof(char) * 10 + 1);
	if(node->filename == NULL)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_strlcpy(node->filename, "/tmp/", 6);
	while (i < 5)
	{
		node->filename[5 + i] = charset[((i) * 1000) % 62];
		i++;
	}
	while(access(node->filename, F_OK) == 0)
	{
		i = 0;
		while (i < 5)
		{
			node->filename[5 + i] = charset[(node->filename[5 + i] + 1) % 62];
			i++;
		}
	}
}
