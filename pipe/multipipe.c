/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:32:13 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/11 14:05:57 by gdanis           ###   ########.fr       */
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

void	ft_read_from_file(char *infile)
{
	int	file;

	file = open(infile, O_RDONLY);
	if (file == -1)
	{
		ft_putstr_fd("read failed\n", 2);
		exit (1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit (1);
	}
	close(file);
}

void	ft_write_to_file(char **outfiles, t_shell *s)
{
	int			file;
	int			old;
	int			i;

	i = 0;
	while (outfiles && outfiles[i])
	{
		if (outfiles[i + 1] != NULL)
		{
			old = open(outfiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (old == -1)
			{
				ft_putstr_fd("fuck write to file failed\n", 2);
				exit (1);
			}
			close(old);
		}
		else
		{
			if (!s->lst->append)
				file = open(outfiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (s->lst->append)
				file = open(outfiles[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (file == -1)
			{
				ft_putstr_fd("fuck write to file failed\n", 2);
				exit (1);
			}
			if (dup2(file, STDOUT_FILENO) == -1)
			{
				ft_putstr_fd("dup2 failed\n", 2);
				exit (1);
			}
			close(file);
		}
		i++;
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
	int		original_stdout;

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
	if (s->cmds == 1 && check_builtin(s->lst))
	{
		original_stdout = dup(1);
		if (s->lst->infile)
			ft_read_from_file(s->lst->infile);
		ft_write_to_file(s->lst->outfiles, s);
		execute_builtin(s, s->lst);
		dup2(original_stdout, 1);
	}
	else
	{
		while (s->lst)
		{
			pid[i] = fork();	
			if (pid[i] == 0)
			{
				printf("im am process %d my arglst[0] is %s\n", i, s->lst->arglst[0]);
				if (s->lst->arglst[0])
				{
					close_unused_pipes(pipes, i, s->cmds);
					if (s->lst->infile)
					{
						ft_read_from_file(s->lst->infile);
						if (i > 0)
							close(pipes[i - 1][0]);
					}
					else if (i > 0)
						ft_read_from_pipe(pipes[i - 1][0]);
					if (s->lst->outfiles)
					{
						ft_write_to_file(s->lst->outfiles, s);
						if (i != (s->cmds - 1))
							close(pipes[i][1]);
					}
					else if (i != (s->cmds - 1))
						ft_write_to_pipe(pipes[i][1]);
					if (check_builtin(s->lst))
					{
						execute_builtin(s, s->lst);
						exit (s->rval);
					}
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
