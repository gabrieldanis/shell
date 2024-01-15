/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:56 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 12:47:01 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_exit(char **args, t_data *data, char **dirs, int ex_code)
{
	if (ex_code == 1)
	{
		free_array(data->dirs);
		free_array(args);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 2)
	{
		if (data && data->dirs)
			free_array(data->dirs);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 4)
	{
		if (dirs)
			free_array(dirs);
		if (data && data->dirs)
			free_array(data->dirs);
		if (args)
			free_array(args);
		ft_printf("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void	free_list(t_plist *lst)
{
	t_plist	*current;
	t_plist	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	wait_for_child(t_plist *lst)
{
	t_plist	*node;

	node = lst;
	while (node->next != NULL)
	{
		waitpid(node->pid, NULL, 0);
		node = node->next;
	}
	waitpid(node->pid, NULL, 0);
}

char	*get_dir_multi(char *str, char **args, t_data *data)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_exit(args, data, NULL, 4);
	i = 0;
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
		free_exit(args, data, dirs, 4);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dirs)
			free_exit(dirs, NULL, NULL, 4);
		if (access(dir, F_OK) == 0)
			return (free(cmd), free_array(dirs), dir);
		free (dir);
		i++;
	}
	return (free(cmd), free_array(dirs), NULL);
}
