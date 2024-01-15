/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:00 by dberes            #+#    #+#             */
/*   Updated: 2024/01/04 11:29:50 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_commands(char **args, t_data *data, int ind)
{
	char	*directory;

	directory = NULL;
	if (access(args[0], F_OK) == 0)
	{
		data->dirs[ind - 2] = ft_strdup(args[0]);
	}
	else
	{
		directory = get_dir(data->path, args, data);
		if (directory == NULL)
			free_exit_commands(args, data, 2);
		data->dirs[ind -2] = ft_strdup(directory);
		free(directory);
	}
}

char	*make_cmd(char **args, char **dirs, t_data *data)
{
	char	*cmd;

	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free(cmd);
		free_dirs(dirs);
		free_exit_execve_malloc(args, data, 2);
	}
	return (cmd);
}

char	*get_dir(char *str, char **args, t_data *data)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_exit_execve_malloc(args, data, 2);
	i = 0;
	cmd = make_cmd(args, dirs, data);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (access(dir, F_OK) == 0)
		{
			free(cmd);
			free_array(dirs);
			return (dir);
		}
		free (dir);
		i++;
	}
	return (free(cmd), free_array(dirs), NULL);
}

void	free_exit_commands(char **args, t_data *data, int ex_code)
{
	if (ex_code == 1)
	{
		if (args)
			free_array(args);
		if (data->dirs)
			free_dirs(data->dirs);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 2)
	{
		if (args[0] == NULL)
			ft_printf("pipex: : command not found\n");
		else
			ft_printf("pipex: %s:command not found\n", args[0]);
		if (args)
			free_array(args);
		if (data->dirs)
			free_dirs(data->dirs);
		exit(EXIT_FAILURE);
	}
}

void	free_exit_execve_malloc(char **args, t_data *data, int ex_code)
{
	if (ex_code == 1)
	{
		free_dirs(data->dirs);
		free_array(args);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 2)
	{
		if (data && data->dirs)
			free_dirs(data->dirs);
		if (args)
			free_array(args);
		ft_printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
}
