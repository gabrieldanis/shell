/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:42:25 by dberes            #+#    #+#             */
/*   Updated: 2024/01/04 13:39:44 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_data(t_data *data, int pipes, char **argv, char **env)
{
	data->path = get_path(env);
	data->env = env;
	data->pipes = pipes;
	data->argv = argv;
	data->argc = 5;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_dirs(char **arr)
{
	if (arr[0])
		free(arr[0]);
	if (arr[1])
		free(arr[1]);
	if (arr)
		free(arr);
}

int	check_args_fd_out(char **args, t_data *data, int fd[2], int *ex)
{
	int		fd_outf;

	if (!args)
	{
		close(fd[0]);
		free_exit_execve_malloc(args, data, 2);
	}
	fd_outf = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: file");
		close(fd[0]);
		*ex = 1;
	}
	if (data->path == NULL || args[0] == NULL)
	{
		close(fd[0]);
		*ex = 2;
	}
	return (fd_outf);
}

int	check_args_fd_in(char **args, t_data *data, int fd[2], int *ex)
{
	int		fd_inf;
	char	*error_msg;

	if (!args)
	{
		close(fd[1]);
		free_exit_execve_malloc(args, data, 2);
	}
	fd_inf = open(data->argv[1], O_RDONLY);
	if (fd_inf == -1)
	{
		close(fd[1]);
		error_msg = ft_strjoin3("pipex: ", data->argv[1], NULL);
		if (!error_msg)
			free_exit_execve_malloc(args, data, 2);
		perror(error_msg);
		free(error_msg);
		*ex = 1;
	}
	if (data->path == NULL || args[0] == NULL)
	{
		close(fd[1]);
		*ex = 2;
	}
	return (fd_inf);
}
