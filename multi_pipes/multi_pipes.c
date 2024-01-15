/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:50 by dberes            #+#    #+#             */
/*   Updated: 2024/01/15 16:05:01 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"



void	dir_copy(t_shell *s, int *ex, int i)
{
	char		*directory;
	t_parsed	*node;

	node = s->lst;
	directory = NULL;
	while(node)
	{
		if (access(node->arglst[0], F_OK) == 0)
			node->cmd = ft_strdup(node->arglst[0]);
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
		node = node->next;
	}
}
/*
void	print_fd_error(t_data *data)
{
	char	*error_msg;

	error_msg = ft_strjoin3("pipex: ", data->argv[1], NULL);
	if (!error_msg)
		free_exit(NULL, data, NULL, 2);
	perror(error_msg);
	free(error_msg);
}
*/
