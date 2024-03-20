/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:11:46 by dberes            #+#    #+#             */
/*   Updated: 2024/03/20 11:18:44 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parse_heredoc(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	char		*line;

	(void) node;
	line = NULL;
	ft_signal_heredoc(s);
	if (subnode->type == HEREDOC)
	{
		create_tmp_file(subnode, s);
		open_heredoc_fd(s, subnode);
		while (1)
		{
			line = heredoc_read(line);
			if (check_eof_error(s, subnode, line) == 1)
				return (1);
			if (heredoc_break(s, subnode, line) == 1)
				break ;
			free_heredoc(s, subnode, line);
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
	char	*varname;
	char	*fstr;

	i = 0;
	fstr = NULL;
	while (line[i])
	{
		varname = NULL;
		while (line[i] && line[i] != '$')
		{
			ft_charjoin(&fstr, line[i], s);
			i++;
		}
		i++;
		s->j_value = i;
		create_var_name(s, line, &varname, &i);
		fstr = create_fstr(s, fstr, varname, line);
	}
	free(line);
	return (fstr);
}

void	create_var_name(t_shell *s, char *line, char **str, int *i)
{
	while (line[*i] && (check_is_var(line[*i]) || line[s->j_value] == '?'))
	{
		ft_charjoin(str, line[*i], s);
		if (line[s->j_value] == '?')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

char	*create_fstr(t_shell *s, char *fstr, char *str, char *line)
{
	char	*tmp;

	if (str)
	{
		if (line[s->j_value] == '?')
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
	return (fstr);
}

void	create_tmp_file(t_parsed *node, t_shell *s)
{
	int			i;
	const char	*charset;

	i = 0;
	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	node->filename = (char *)malloc(sizeof(char) * 10 + 1);
	if (node->filename == NULL)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_strlcpy(node->filename, "/tmp/", 6);
	while (i < 5)
	{
		node->filename[5 + i] = charset[((i) * 1000) % 62];
		i++;
	}
	node->filename[10] = '\0';
	while (access(node->filename, F_OK) == 0)
	{
		i = 0;
		while (i < 5)
		{
			node->filename[5 + i] = charset[(node->filename[5 + i] * 3) % 62];
			i++;
		}
	}
}
