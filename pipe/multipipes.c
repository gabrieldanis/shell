/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:32:13 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/08 22:04:55 by gdanis           ###   ########.fr       */
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

void	close_unused_pipes(int **pipes, int i, int argc)
{
	int	j;
	
	j = 0;
	while (j < (argc - 2))
	{
		if (j != (i - 1))
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

int	main(int argc, char *argv[])
{
	char	***cmds;
	int		*pid;
	int		**pipes;
	int		i;
	
	if (argc == 1)
		return (printf("not enough arguments\n"), 0);
	pid = (int *)malloc(sizeof(int) * (argc - 1));
	if (!pid)
		return (1);
	if (argc > 2)
	{
		pipes =(int **)malloc(sizeof(int *) * (argc - 2));
		if (!pipes)
			return 1;
	}
	i = 0;
	while (i < argc - 2)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	cmds = (char ***)malloc(sizeof(char **) * (argc - 1));
	if (!cmds)
		return (1);
	i = 0;
	while (i < argc - 1)
	{
		cmds[i] = ft_split(argv[i + 1], ' ');
		if (!cmds[i])
			return (1);
		i++;
	}
	i = 0;
	while (i < argc - 2)
	{
		pipe(pipes[i]);	
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		pid[i] = fork();	
		if (pid[i] == 0)
		{
			close_unused_pipes(pipes, i, argc);
			if (i > 0)
				ft_read_from_pipe(pipes[i - 1][0], i);
			if (i != (argc - 2))
				ft_write_to_pipe(pipes[i][1], i);
			if (execvp(cmds[i][0], cmds[i]) == -1)
			{
				ft_putstr_fd("execvp failed\n", 2);
				exit (1);
			}
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < argc - 2)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		wait(NULL);
		i++;
	}
	printf("all processes have finished ... I think. \n");

	return (0);
}
