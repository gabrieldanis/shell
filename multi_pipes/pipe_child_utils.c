/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:50:37 by dberes            #+#    #+#             */
/*   Updated: 2024/04/08 12:52:20 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	child_process_error_check(t_shell *s, t_parsed *node)
{
	if (!node->arglst || !node->arglst[0])
		free_and_exit(0, s, NULL, NULL);
	if (node->cmd[0] && (node->cmd[ft_strlen(node->cmd) - 1] == '/'
			|| (ft_strchr(node->cmd, '/') && !node->cmd_found)))
	{
		if (access(node->cmd, F_OK))
			free_and_exit(NOFILE_ERROR, s, NULL, node->arglst[0]);
		errno = 21;
		free_and_exit(ISDIR_ERROR, s, NULL, node->arglst[0]);
	}
	if (!ft_strncmp(node->arglst[0], "exit\0", 5))
		free_and_exit(0, s, NULL, NULL);
	if (execute_builtin(s, node))
		free_and_exit(0, s, NULL, NULL);
	if (s->path && !node->cmd_found)
		free_and_exit(CMD_ERROR, s, NULL, node->arglst[0]);
	if (!s->path && !node->cmd_found)
	{
		errno = 2;
		free_and_exit(NOFILE_ERROR, s, NULL, node->arglst[0]);
	}
	if ((node->cmd || !s->path) && access(node->cmd, X_OK) != 0)
		free_and_exit(PERM_ERROR, s, NULL, node->arglst[0]);
	call_execve(s, node);
}

void	ft_write_to_file(t_shell *s, t_parsed *node)
{
	int			file;
	int			i;

	i = 0;
	while (node->outfiles && node->outfiles[i + 1])
		i++;
	if (node->outfiles && node->outfiles[i])
	{
		if (!node->append)
			file = open(node->outfiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (node->append)
			file = open(node->outfiles[i], O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (file == -1 && !s->builtin)
			free_and_exit(0, s, NULL, NULL);
		if (dup2(file, STDOUT_FILENO) == -1 && !s->builtin)
		{
			fd_closer(s);
			free_and_exit(DUP_ERROR, s, NULL, NULL);
		}
		close(file);
	}
}

int	check_infiles(t_shell *s, t_parsed *lst)
{
	t_parsed	*node;

	node = lst->lst;
	while (node)
	{
		if (node->type == INFILE && access(node->str, F_OK) != 0)
		{
			if (s->builtin != 0)
				return (error_message(NOINFILE_ERROR, NULL, node->str, s), 1);
			else
				free_and_exit(NOINFILE_ERROR, s, NULL, node->str);
		}
		else if (node->type == INFILE && access(node->str, R_OK) != 0)
		{
			if (s->builtin != 0)
				return (error_message(PERM_ERROR, NULL, node->str, s), 1);
			else
				free_and_exit(PERM_ERROR, s, NULL, node->str);
		}
		node = node->next;
	}
	return (0);
}

void	count_parsed_nodes(t_shell *s)
{
	t_parsed	*node;

	s->cmds = 0;
	node = s->lst;
	while (node)
	{
		s->cmds++;
		node = node->next;
	}
}

t_parsed	*get_to_node(t_parsed *node, int ind)
{
	int	i;

	i = 0;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	return (node);
}
