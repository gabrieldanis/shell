/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/19 16:31:29 by dberes           ###   ########.fr       */
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
					lstlast(lstlast(s->lst)->lst)->heredoc_quote = s->tlst->heredoc_quote;
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
	if (lst->type == HEREDOC)
	{
		s->lst->infile = lst->filename;
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

int	check_delimiter(t_parsed *node, t_shell *s)
{
	if (!node->next)
	{
		error_message(NO_DELIMIT_ERROR, NULL, NULL, s);
		return (1);
	}
	else if (*(node->next->str) == '|')
	{
		error_message(DELIMIT_ERROR, NULL, node->next->str, s);
		return (1);	
	}
	else
		return (0);
}

int	parse_heredoc(t_parsed *lst, t_shell *s)
{
	char		*line;
	char		*line_new;
	t_parsed	*node;
	
	node = lst;
	line = NULL;
	line_new = NULL;
	//while(node)
	//{
	ft_signal_heredoc(s);
	if (node->type == HEREDOC)
	{
		if (check_delimiter(node, s))
		{
			s->rval = 2;
			return (-1);
		}
		create_tmp_file(node, s);
		s->heredocfd = open(node->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (s->heredocfd == -1) 
		{
    		perror("Error opening file");
    		free_and_exit(OPEN_ERROR, s, NULL, NULL);
		}
		while (1)
		{
			line = readline("> ");
			if(!line)
			{
				error_message(HEREDOC_EOF_ERROR, "warning", node->next->str, s);
				return (1);
			}
			if (!ft_strncmp(line, node->next->str, ft_strlen(line) +1))
				break ;
			if (g_var == 130)
			{
				s->rval = g_var;
				break ;
			}
			if (ft_strchr(line, '$') && node->next->heredoc_quote == 0)
				line = heredoc_expand(line, s); 
			line_new = ft_strjoin(line, "\n");
			if(!line_new)
			{
				free(line);
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			}
			if(write(s->heredocfd, line_new, ft_strlen(line_new)) == -1)
				free_and_exit(WRITE_ERROR, s, NULL, NULL);
		}
		if (line_new)
			free(line_new);
	}
	//node = node->next;
	//}
	return (1);
}

char	*heredoc_expand(char *line, t_shell *s)
{
	int		i;
	int		j;
	char	*str;
	char	*fstr;
	char	*tmp;
	

	i = 0;

	fstr = NULL;
	while (line[i])
	{
		str = NULL;
		while (line[i] && line[i] != '$')
		{
			ft_charjoin(&fstr, line[i], s);
			i++;
		}
		i++;
		j = i;
		while (line[i] && (check_is_var(line[i]) || line[j] == '?'))
		{
			ft_charjoin(&str, line[i], s);
			if (line[j] == '?')
			{
				i++;
				break ;
			}
			i++;
		}
		if (str)
		{
			if (line[j] == '?')
				tmp = ft_strjoin(fstr, token_vardup(NULL, s, EXIT_VALUE));
			else
				tmp = ft_strjoin(fstr, getenv(str));
			if (!tmp)
			{
				free(str);
				free(fstr);
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			}
			free(str);
			free(fstr);
			fstr = tmp;
		}
	}
	free(line);
	return (fstr);
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
			node->filename[5 + i] = charset[(node->filename[5 + i] * 329) % 62];
			i++;
		}
	}
}
