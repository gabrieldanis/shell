/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/15 12:49:01 by gdanis           ###   ########.fr       */
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
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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
	t_token	*t_node;
	t_token	*ex_node;

	t_node = s->tlst;
	while (t_node)
	{
		addnewlstback(s, NULL);
		while (t_node && t_node->type != PIPE)
		{
			ex_node = t_node->ex;
			while (ex_node)	
			{
				if (ex_node->str)
				{
					addnewlstback(s, lstlast(s->lst));
					node_dup(lstlast(lstlast(s->lst)->lst), t_node, ex_node->str, s);
					lstlast(lstlast(s->lst)->lst)->heredoc_quote = t_node->heredoc_quote;
				}
				ex_node = ex_node->next;
			}
			t_node = t_node->next;
		}
		if (t_node && t_node->type == PIPE)
		{
			addnewlstback(s, lstlast(s->lst));
			node_dup(lstlast(lstlast(s->lst)->lst), t_node, t_node->str, s);
			t_node = t_node->next;
		}
	}
}

void	node_dup(t_parsed *node, t_token *t_node, char *s2, t_shell *s)
{
	node->str = ft_strdup(s2);
	if (!node->str)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	node->type = t_node->type;

}

int	parse_isfile(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	/*
	if ((lst->type == RED_IN || lst->type == RED_OUT 
		||lst->type == RED_APP) && lst->next)
	{
		if (lst->next->type)
		{
			error_message(UNEX_TOKEN, NULL, lst->next->str, s);
			return (0);
		}
	}
	*/
	if (subnode->type == RED_IN && subnode->next && !subnode->next->type)
	{
		subnode->next->type = INFILE;
		node->infile = subnode->next->str;
	}
	if (subnode->type == HEREDOC)
		node->infile = subnode->filename;
	if ((subnode->type == RED_OUT || subnode->type == RED_APP) && subnode->next
			&& !subnode->next->type)
	{
		subnode->next->type = OUTFILE;
		appln_chararr(node, subnode->next->str, s);
		if (subnode->type == RED_OUT)
			node->append = 0;
		else
			node->append = 1;
	}
	return (1);
}

int	parse_cmdargs(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	static int	cmd;

	(void)s;
	(void)node;
	if (!subnode->type && !cmd)
	{
		subnode->type = CMD;
		cmd = 1;
	}
	if (!subnode->type && cmd)
		subnode->type = ARG;
	if (!subnode->next)
		cmd = 0;
	return (1);
}

int	parse_heredoc(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	char		*line;
	char		*line_new;
	
	(void) node;
	line = NULL;
	line_new = NULL;
	ft_signal_heredoc(s);
	if (subnode->type == HEREDOC)
	{
		//node->infile = 1;
		create_tmp_file(subnode, s);
		s->heredocfd = open(subnode->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (s->heredocfd == -1) 
		{
    		perror("Error opening file");
    		free_and_exit(OPEN_ERROR, s, NULL, NULL);
		}
		while (1)
		{
			if((isatty(0)))
				line = readline("> ");
			else
			{
				line = get_next_line(0);
				if (line && ft_strlen(line) > 0 && line[(ft_strlen(line)) - 1] == '\n')
					line[ft_strlen(line) - 1] = '\0';
			}
			if(!line)
			{
				error_message(HEREDOC_EOF_ERROR, "warning", subnode->next->str, s);
				return (1);
			}
			if (!ft_strncmp(line, subnode->next->str, ft_strlen(line) + 1))
				break ;
			if (g_var == 130)
			{
				s->rval = g_var;
				break ;
			}
			if (ft_strchr(line, '$') && subnode->next->heredoc_quote == 0)
				line = heredoc_expand(line, s); 
			line_new = ft_strjoin(line, "\n");
			if(!line_new)
			{
				free(line);
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			}
			free(line);
			line = NULL;
			if(write(s->heredocfd, line_new, ft_strlen(line_new)) == -1)
			{
				free(line_new);
				free_and_exit(WRITE_ERROR, s, NULL, NULL);
			}
			if (line_new)
				free(line_new);
		}
		if (line)
			free(line);
		close(s->heredocfd);
	}
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
				free(line);
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
    int            i;
    const char    *charset;

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
	node->filename[10] = '\0';
    while(access(node->filename, F_OK) == 0)
    {
        i = 0;
        while (i < 5)
        {
            node->filename[5 + i] = charset[(node->filename[5 + i] * 3) % 62];
            i++;
        }
    }
}
