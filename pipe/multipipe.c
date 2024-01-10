/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:32:13 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/09 22:02:12 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_write_to_pipe(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit (1);
	}
	close(fd);
}

void	ft_read_from_pipe(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit (1);
	}
	close(fd);
}

void	close_unused_pipes(int **pipes, int i, int cmds)
{
	int	j;
	
	j = 0;
	while (j < (cmds - 1))
	{
		if (j != (i - 1))
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

void	count_parsed_nodes(t_shell *s)
{
	t_parsed *start;

	start = s->lst;
	while (s->lst)
	{
		s->cmds++;
		s->lst = s->lst->next;	
	}
	s->lst = start;
}

void	multipipe(t_shell *s)
{
	t_parsed	*start;
	int		*pid;
	int		**pipes;
	int		i;

	start = s->lst;
	count_parsed_nodes(s);
	add_path_to_cmd(s);
	pid = (int *)malloc(sizeof(int) * (s->cmds));
	if (!pid)
		free_and_exit(MALLOC_ERROR, s);
	if (s->cmds > 1)
	{
		pipes =(int **)malloc(sizeof(int *) * (s->cmds - 1));
		if (!pipes)
			free_and_exit(MALLOC_ERROR, s);
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		// free here backwards aswell
		i++;
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		pipe(pipes[i]);	
		i++;
	}
	i = 0;
	while (s->lst)
	{
		pid[i] = fork();	
		if (pid[i] == 0)
		{
			printf("im am process %d my arglst[0] is %s\n", i, s->lst->arglst[0]);
			if (s->lst->cmd)
			{
				close_unused_pipes(pipes, i, s->cmds);
				if (i > 0)
					ft_read_from_pipe(pipes[i - 1][0]);
				if (i != (s->cmds - 1))
					ft_write_to_pipe(pipes[i][1]);
				if (execve(s->lst->cmd, s->lst->arglst, s->env) == -1)
					ft_putstr_fd("execve failed\n", 2);
			}
			else
			{
				i = 0;
				while (i < s->cmds - 1)
				{
					close(pipes[i][0]);
					close(pipes[i][1]);
					i++;
				}
				return ;
			}
		}
		i++;
		s->lst = s->lst->next;
	}
	i = 0;
	while (i < s->cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < s->cmds)
	{
		wait(NULL);
		i++;
	}
	s->lst = start;
	printf("all processes have finished ... I think. \n");
}
