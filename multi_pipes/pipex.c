/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:01:58 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 14:03:02 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd[2], t_data *data, int ind)
{
	char	**args1;
	int		fd_inf;
	int		ex;

	ex = 0;
	close(fd[0]);
	args1 = ft_split(data->argv[ind], 32);
	fd_inf = check_args_fd_in(args1, data, fd, &ex);
	dirs_calloc(data);
	if (ex != 2)
		check_commands(args1, data, 2);
	if (ex != 0)
		free_exit_commands(args1, data, ex);
	if (dup2(fd_inf, STDIN_FILENO) == -1)
		dup_fail(args1, data, fd[1], fd_inf);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		dup_fail(args1, data, fd[1], fd_inf);
	close(fd_inf);
	close(fd[1]);
	if (execve(data->dirs[0], args1, data->env) == -1)
		free_exit_execve_malloc(args1, data, 1);
}

void	parent_process(int fd[2], t_data *data, int ind)
{
	char	**args2;
	int		ex;
	int		fd_outf;

	ex = 0;
	close(fd[1]);
	args2 = ft_split(data->argv[ind], 32);
	fd_outf = check_args_fd_out(args2, data, fd, &ex);
	dirs_calloc(data);
	if (ex != 2)
		check_commands(args2, data, 3);
	if (ex != 0)
		free_exit_commands(args2, data, ex);
	if (dup2(fd_outf, STDOUT_FILENO) == -1)
		dup_fail(args2, data, fd[0], fd_outf);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		dup_fail(args2, data, fd[0], fd_outf);
	close(fd[0]);
	close(fd_outf);
	if (execve(data->dirs[1], args2, data->env) == -1)
		free_exit_execve_malloc(args2, data, 1);
}

int	single_pipe(char **argv, char **env)
{
	int		fd[2];
	int		pid;
	t_data	data;

	set_data(&data, 1, argv, env);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
		child_process(fd, &data, 2);
	else
		parent_process(fd, &data, 3);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		if (single_pipe(argv, env) != 0)
			return (2);
		return (0);
	}
	else
	{
		ft_printf("wrong input");
		exit(EXIT_FAILURE);
	}
}
