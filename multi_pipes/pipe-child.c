/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:32 by dberes            #+#    #+#             */
/*   Updated: 2024/04/05 21:37:21 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	multi_child_process(t_parsed *lst, t_shell *s, int ind)
{
	t_parsed	*node;

	node = lst;
	node = get_to_node(node, ind);
	if (create_node_outfiles(s, node))
	{
		fd_closer(s);
		free_and_exit(0, s, NULL, NULL);
	}
	if (node->infile)
		fd_opener(node, s);
	else if (ind > 0)
	{
		if (dup2(s->pipes[ind -1][0], STDIN_FILENO) == -1)
		{
			free_and_exit(DUP_ERROR, s, NULL, NULL);
		}
	}
	if (node->outfiles)
		ft_write_to_file(s, node);
	else if (s->cmds > 1 && ind < s->cmds -1)
	{
		if (dup2(s->pipes[ind][1], STDOUT_FILENO) == -1)
			free_and_exit(DUP_ERROR, s, NULL, NULL);
	}
	fd_closer(s);
	child_process_error_check(s, node);
}

void	fd_opener(t_parsed *lst, t_shell *s)
{
	check_infiles(s, lst);
	if (s->error == 0)
		lst->fd_inf = open(lst->infile, O_RDONLY);
	if (lst->fd_inf == -1 && s->builtin == 0)
		free_and_exit(NOFILE_ERROR, s, NULL, lst->infile);
	if (dup2(lst->fd_inf, STDIN_FILENO) == -1 && s->builtin == 0)
	{
		close(lst->fd_inf);
		free_and_exit(DUP_ERROR, s, NULL, NULL);
	}
	close(lst->fd_inf);
}

void	fd_closer(t_shell *s)
{
	int	i;

	i = 0;
	if (!s->pipes)
		return ;
	while (i < s->cmds - 1)
	{
		close(s->pipes[i][0]);
		close(s->pipes[i][1]);
		i++;
	}
}
