/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:50 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 15:32:08 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_closer(int end, t_plist **lst)
{
	t_plist	*node;

	node = *lst;
	if (list_size(lst) == 1)
	{
		close (node->fd[0]);
		close (node->fd[1]);
	}
	else
	{
		while (node->next->next != NULL)
		{
			close (node->fd[0]);
			close (node->fd[1]);
			node = node->next;
		}
	}
	if (end == 1)
		close (node->fd[1]);
	else
	{
		close (node->fd[0]);
		close (node->fd[1]);
	}
}

void	dir_copy(char **args, t_data *data, int *ex, int i)
{
	char	*directory;

	directory = NULL;
	if (access(args[0], F_OK) == 0)
		data->dirs[i - 2] = ft_strdup(args[0]);
	else
	{
		directory = get_dir_multi(data->path, args, data);
		if (directory == NULL)
		{
			ft_printf("pipex: %s: command not found\n", args[0]);
			*ex = 1;
		}
		else if (*ex == 0)
			data->dirs[i - 2] = ft_strdup(directory);
		free(directory);
	}
}

void	print_fd_error(t_data *data)
{
	char	*error_msg;

	error_msg = ft_strjoin3("pipex: ", data->argv[1], NULL);
	if (!error_msg)
		free_exit(NULL, data, NULL, 2);
	perror(error_msg);
	free(error_msg);
}
