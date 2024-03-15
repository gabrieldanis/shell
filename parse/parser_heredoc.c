/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:11:46 by dberes            #+#    #+#             */
/*   Updated: 2024/03/15 17:12:31 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
		create_tmp_file(subnode, s);
		s->heredocfd = open(subnode->filename, O_WRONLY | O_APPEND
				| O_CREAT, 0644);
		if (s->heredocfd == -1)
		{
			perror("Error opening file");
			free_and_exit(OPEN_ERROR, s, NULL, NULL);
		}
		while (1)
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
			if (!line)
			{
				error_message(HEREDOC_EOF_ERROR, "warning",
					subnode->next->str, s);
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
