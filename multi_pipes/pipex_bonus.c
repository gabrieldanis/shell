/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:14:28 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 14:11:20 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_processes(t_plist **lst, t_data *data, int ind)
{
	if (ind == 0)
		first_child_process(lst, data, ind);
	else if (ind != data->pipes)
		multi_child_process(lst, data, ind - 1);
	else
		last_child_process(lst, data, ind);
	exit(EXIT_SUCCESS);
}

void	multi_parent(t_plist *lst)
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

void	pipe_fork(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;

	node = (t_plist *)malloc(sizeof(t_plist));
	if (node == NULL)
		return ;
	*node = (t_plist){0};
	if (ind < data->pipes)
	{
		if (pipe(node->fd) == -1)
		{
			free_array(data->dirs);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	node->pid = fork();
	if (node->pid == -1)
		return ;
	add_pipe_node(lst, node);
	if (node->pid == 0)
		child_processes(lst, data, ind);
}

int	multi_pipe(int pipes, char **argv, char **env, int argc)
{
	int		i;
	int		ex;
	t_plist	*lst;
	t_data	data;		

	ex = 0;
	set_data_bonus(&data, pipes, argv, env);
	data.argc = argc;
	file_create(&data);
	if (data.path == NULL)
		path_error(&data);
	dirs_calloc(&data);
	check_args(&data, &ex);
	i = 0;
	lst = NULL;
	check_commands_bonus(&data, &ex);
	while (i < argc - 3)
	{
		pipe_fork(&lst, &data, i);
		i++;
	}
	multi_parent(lst);
	wait_for_child(lst);
	return (free_list(lst), free_array(data.dirs), 0);
}

int	main(int argc, char **argv, char **env)
{
	int	pipes;

	pipes = argc - 4;
	if (argc < 5)
	{
		ft_printf("wrong input");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (multi_pipe(pipes, argv, env, argc) != 0)
			return (3);
		return (0);
	}
}
