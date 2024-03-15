/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:32 by dberes            #+#    #+#             */
/*   Updated: 2024/03/13 11:54:15 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	multi_child_process(t_parsed *lst, t_shell *s, int ind)
{
	t_parsed	*node;

	node = lst;
	node = get_to_node(node, ind);
	if (node->infile)
		fd_opener(node, s);
	else if (ind > 0)
	{
		if (dup2(s->pipes[ind -1][0], STDIN_FILENO) == -1)
			free_and_exit(DUP_ERROR, s, NULL, NULL);
	}
	if (node->outfiles)
		ft_write_to_file(s, node);
	else if (s->cmds > 1 && ind < s->cmds -1)
	{
		if (dup2(s->pipes[ind][1], STDOUT_FILENO) == -1)
			free_and_exit(DUP_ERROR, s, NULL, NULL);
	}
	fd_closer(s);
	if (!node->arglst || !node->arglst[0])
		free_and_exit(0, s, NULL, NULL);
	if (node->cmd[ft_strlen(node->cmd) - 1] == '/'
		|| (ft_strchr(node->cmd, '/') && !node->cmd_found))
	{
		if (access(node->cmd, F_OK))
			free_and_exit(NOFILE_ERROR, s, NULL, node->arglst[0]);
		errno = 21;
		free_and_exit(ISDIR_ERROR, s, NULL, node->arglst[0]);
	}
	if (execute_builtin(s, node))
		free_and_exit(0, s, NULL, NULL);
	if (s->path && !node->cmd_found)
		free_and_exit(CMD_ERROR, s, NULL, node->arglst[0]);
	if (!s->path && !node->cmd_found)
		free_and_exit(NOFILE_ERROR, s, NULL, node->arglst[0]);
	if ((node->cmd || !s->path) && access(node->cmd, X_OK) != 0)
		free_and_exit(PERM_ERROR, s, NULL, node->arglst[0]);
	if (execve(node->cmd, node->arglst, s->env) == -1)
		free_and_exit(EXECVE_ERROR, s, NULL, node->arglst[0]);
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
			file = open(node->outfiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (node->append)
			file = open(node->outfiles[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (file == -1)
			free_and_exit(0, s, NULL, NULL);
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			fd_closer(s);
			free_and_exit(DUP_ERROR, s, NULL, NULL);
		}
		close(file);
	}
}

void	check_infiles(t_shell *s, t_parsed *lst)
{
	t_parsed	*node;

	node = lst->lst;
	while (node)
	{
		if (node->type == INFILE && access(node->str, F_OK) != 0)
			free_and_exit(NOINFILE_ERROR, s, NULL, node->str);
		if (node->type == INFILE && access(node->str, R_OK) != 0)
			free_and_exit(PERM_ERROR, s, NULL, node->str);
		node = node->next;
	}
}

void	fd_opener(t_parsed *lst, t_shell *s)
{
	check_infiles(s, lst);
	lst->fd_inf = open(lst->infile, O_RDONLY);
	if (lst->fd_inf == -1)
		free_and_exit(NOFILE_ERROR, s, NULL, lst->infile);
	if (dup2(lst->fd_inf, STDIN_FILENO) == -1)
		free_and_exit(DUP_ERROR, s, NULL, NULL);
	close(lst->fd_inf);
}

void	fd_closer(t_shell *s)
{
	int	i;

	i = 0;
	while (i < s->cmds - 1)
	{
		close(s->pipes[i][0]);
		close(s->pipes[i][1]);
		i++;
	}
}
