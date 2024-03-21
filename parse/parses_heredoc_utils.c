/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parses_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:51:10 by dberes            #+#    #+#             */
/*   Updated: 2024/03/21 15:15:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_eof_error(t_shell *s, t_parsed *subnode, char *line)
{
	if (!line)
	{
		close(s->heredocfd);
		error_message(HEREDOC_EOF_ERROR, "warning",
			subnode->next->str, s);
		return (1);
	}
	return (0);
}

int	heredoc_break(t_shell *s, t_parsed *subnode, char *line)
{
	if (!ft_strncmp(line, subnode->next->str, ft_strlen(line) + 1))
	{
		return (1);
	}
	if (g_var == 130)
	{
		s->rval = g_var;
		return (1);
	}
	return (0);
}

char	*heredoc_read(char *line)
{
	if ((isatty(0)))
		line = readline("> ");
	else
	{
		line = get_next_line(0);
		if (line && ft_strlen(line) > 0
			&& line[(ft_strlen(line)) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

void	free_heredoc(t_shell *s, t_parsed *subnode, char *line)
{
	char		*line_new;

	line_new = NULL;
	if (ft_strchr(line, '$') && subnode->next->heredoc_quote == 0)
		line = heredoc_expand(line, s);
	line_new = ft_strjoin(line, "\n");
	if (!line_new)
	{
		free(line);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	free(line);
	line = NULL;
	if (write(s->heredocfd, line_new, ft_strlen(line_new)) == -1)
	{
		free(line_new);
		free_and_exit(WRITE_ERROR, s, NULL, NULL);
	}
	if (line_new)
		free(line_new);
}

void	open_heredoc_fd(t_shell *s, t_parsed *subnode)
{
	s->heredocfd = open(subnode->filename, O_WRONLY | O_APPEND
			| O_CREAT, 0644);
	if (s->heredocfd == -1)
	{
		perror("Error opening file");
		free_and_exit(OPEN_ERROR, s, NULL, NULL);
	}
}
