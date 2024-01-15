/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:32 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 15:18:27 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_process(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	char	**args;

	node = *lst;
	args = ft_split(data->argv[ind + 2], 32);
	if (dup2(data->fd_inf, STDIN_FILENO) == -1)
		dup_fail(args, data, node->fd[1], lst);
	if (dup2(node->fd[1], STDOUT_FILENO) == -1)
		dup_fail(args, data, node->fd[1], lst);
	close(data->fd_inf);
	fd_closer(0, lst);
	if (execve(data->dirs[ind], args, data->env) == -1)
		free_exit(args, data, NULL, 1);
}

void	multi_child_process(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	char	**args;

	node = *lst;
	node = get_to_node(node, ind + 1);
	if (dup2(node->fd[0], STDIN_FILENO) == -1)
		dup_fail(NULL, data, node->fd[0], NULL);
	if (dup2(node->next->fd[1], STDOUT_FILENO) == -1)
		dup_fail(NULL, data, node->next->fd[1], NULL);
	fd_closer(0, lst);
	args = ft_split(data->argv[ind + 3], 32);
	if (!args)
		free_exit(args, data, NULL, 4);
	if (execve(data->dirs[ind + 1], args, data->env) == -1)
		free_exit(args, data, NULL, 1);
}

void	last_child_process(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	char	**args;

	args = ft_split(data->argv[ind + 2], 32);
	if (!args)
		free_exit(args, data, NULL, 4);
	node = *lst;
	node = get_to_node(node, ind);
	fd_closer(1, lst);
	data->fd_outf = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data->fd_outf == -1)
		fd_fail(args, data, node->fd[0], lst);
	if (dup2(data->fd_outf, STDOUT_FILENO) == -1)
		dup_fail(args, data, node->fd[0], lst);
	if (dup2(node->fd[0], STDIN_FILENO) == -1)
		dup_fail(args, data, node->fd[0], lst);
	close (node->fd[0]);
	close(data->fd_outf);
	if (execve(data->dirs[ind], args, data->env) == -1)
		free_exit(args, data, NULL, 1);
}
