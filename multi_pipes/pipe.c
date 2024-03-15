/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:14:11 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/08 17:15:51 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	multi_pipe(t_shell *s)
{
	s->path = get_path(s->env);
	if (get_dir_multi(s) != 0)
		return (0);
	pipe_array(s);
	if (s->cmds)
		pipe_fork(s->lst, s);
	fd_closer(s);
	wait_for_child(s);
	return (0);
}

void	wait_for_child(t_shell *s)
{
	t_parsed	*node;
	int			status;

	node = s->lst;
	while (node->next != NULL)
	{
		waitpid(node->pid, &status, 0);
		node = node->next;
	}
	waitpid(node->pid, &status, 0);
	if (WIFEXITED(status))
		s->rval = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		s->rval = 128 + WTERMSIG(status);
	ft_signal(s);
}

void	pipe_array(t_shell *s)
{
	int	i;

	if (s->cmds > 1)
	{
		s->pipes = (int **)malloc(sizeof(int *) * (s->cmds - 1));
		if (!s->pipes)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		if (pipe(s->pipes[i]) == -1)
			free_and_exit(PIPE_ERROR, s, NULL, NULL);
		i++;
	}
}

void	pipe_fork(t_parsed *lst, t_shell *s)
{
	int			ind;
	t_parsed	*node;

	node = lst;
	ind = 0;
	while (node)
	{
		child_signal();
		node->pid = fork();
		if (node->pid == -1)
			free_and_exit(PID_ERROR, s, NULL, NULL);
		if (node->pid == 0)
			multi_child_process(lst, s, ind);
		ind++;
		node = node->next;
	}
}
