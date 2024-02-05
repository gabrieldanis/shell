/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:14:11 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/05 13:39:30 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	multi_pipe(t_shell *s)
{
	int		i;
	/*int		ex;

	ex = 0;*/
	s->path = get_path(s->env);
	get_dir_multi(s);
	/*file_create(&data);
	if (s.path == NULL)
		path_error(&data);
	check_args(&data, &ex);
	check_commands_bonus(&data, &ex);*/
	pipe_array(s);
	i = 0;
	while (i < s->cmds)
	{
		pipe_fork(s->lst, s, i);
		printf("5\n");
		i++;
	}
	close_all_pipes(s);
	wait_for_child(s);
	//return (free_list(s), free_array(s->lst->dirs), 0);
	return (0);
}

void	wait_for_child(t_shell *s)
{
	t_parsed	*node;

	node = s->lst;
	while (node->next != NULL)
	{
		waitpid(node->pid, NULL, 0);
		node = node->next;
	}
	waitpid(node->pid, NULL, 0);
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
		if (pipe(s->pipes[i]) == -1)
			free_and_exit(PIPE_ERROR, s);
		i++;
	}
}

void	pipe_fork(t_parsed *lst, t_shell *s, int ind)
{
	t_parsed	*node;

	node = lst;
	while (node)
	{
		
		lst->pid = fork();
		if (lst->pid == -1)
			free_and_exit(PID_ERROR, s);
		if (lst->pid == 0)
			multi_child_process(lst, s, ind);
		node = node->next;
	}
}

void	close_all_pipes(t_shell *s)
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
