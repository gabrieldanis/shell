/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:14:28 by dberes            #+#    #+#             */
/*   Updated: 2024/01/15 13:18:45 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	child_processes(t_parsed *lst, t_shell *s, int ind)
{
	if (ind == 0)
		first_child_process(lst, s, ind);
	else if (ind != s->cmds - 1)
		multi_child_process(lst, s, ind - 1);
	else
		last_child_process(lst, s, ind);
	/*exit(EXIT_SUCCESS);*/
}

void	multi_parent(t_parsed *lst)
{
	t_plist	*node;

	node = lst;
	while (node != NULL)
	{
		close (node->fd[0]);
		close (node->fd[1]);
		node = node->next;
	}
}

void	pipe_fork(t_parsed *lst, t_shell *s, int ind)
{
	lst->pid = fork();
	if (lst->pid == -1)
		free_and_exit(PID_ERROR, s);
	if (lst->pid == 0)
		child_processes(lst, s, ind);
}

void	pipe_array(t_shell *s)
{
	int	i;

	if (s->cmds > 1)
	{
		s->pipes =(int **)malloc(sizeof(int *) * (s->cmds - 1));
		if (!s->pipes)
			free_and_exit(MALLOC_ERROR, s);
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		// free here backwards aswell
		i++;
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		if (pipe(s->pipes[i] == -1))
			free_and_exit(PIPE_ERROR, s);
		i++;
	}
}

int	multi_pipe(t_shell *s)
{
	int		i;
	int		ex;
	t_plist	*lst;
	t_data	data;		

	ex = 0;
	s->path = get_path(s->env);
	/*file_create(&data);
	if (s.path == NULL)
		path_error(&data);
	check_args(&data, &ex);
	check_commands_bonus(&data, &ex);*/
	pipe_array(s);
	i = 0;
	while (i < s->cmds - 1)
	{
		pipe_fork(s->lst, s, i);
		i++;
	}
	multi_parent(s);
	wait_for_child(s);
	return (free_list(s), free_array(s->lst->dirs), 0);
}
