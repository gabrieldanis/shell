/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:32 by dberes            #+#    #+#             */
/*   Updated: 2024/02/05 13:36:54 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	multi_child_process(t_parsed *lst, t_shell *s, int ind)
{
	t_parsed	*node;

	node = lst;
	node = get_to_node(node, ind);
	if (node->infile)
		fd_opener(node, s);
	else if (ind > 0)
	{
		if (dup2(s->pipes[ind -1][0], STDIN_FILENO) == -1)
		{
			/*fd_closer(0, lst);*/
			free_and_exit(DUP_ERROR, s);
		}
	}
	if (s->cmds > 1 && dup2(s->pipes[ind][1], STDOUT_FILENO) == -1)
	{
			/*fd_closer(0, lst);*/
			free_and_exit(DUP_ERROR, s);
	}	
	fd_closer(s);
	printf ("%s \n", node->cmd);
	printf ("%s \n", s->env[0]);
	if (execve(node->cmd, node->arglst, s->env) == -1)
		free_and_exit(EXECVE_ERROR, s);
}

void	fd_opener(t_parsed *lst, t_shell *s)
{
	lst->fd_inf = open(lst->infile, O_RDONLY);
	/*if (lst->fd_inf == -1)
	{
		print_fd_error(data);
		*ex = 1;
	}*/
	if (dup2(lst->fd_inf, STDIN_FILENO) == -1)
	{
			//dup_fail(args, s, node->fd[1], lst);
			free_and_exit(DUP_ERROR, s);
	}
}

void	fd_closer(t_shell *s)
{
	int	i;

	i = 0;
	while (i < s->cmds - 1)
	{
		close(s->pipes[i][0]);
		close(s->pipes[i][1]);
		i++;
	}
}

/*void	file_create(t_data *data)
{
	data->fd_outf = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data->fd_outf == -1)
	{
		perror("pipex: failed to open outfile");
		close(data->fd_outf);
		exit(EXIT_FAILURE);
	}
	close(data->fd_outf);
}*/
/*
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

void	first_child_process(t_parsed *lst, t_shell *s, int ind)
{
	if (lst->infile)
		fd_opener(lst, s);
	if (dup2(lst->fd_inf, STDIN_FILENO) == -1)
		dup_fail(args, data, node->fd[1], lst);
	if (dup2(node->fd[1], STDOUT_FILENO) == -1)
		dup_fail(args, data, node->fd[1], lst);
	close(data->fd_inf);
	fd_closer(0, lst);
	if (execve(data->dirs[ind], args, data->env) == -1)
		free_exit(args, data, NULL, 1);
}
*/
