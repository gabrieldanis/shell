/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:55:12 by dberes            #+#    #+#             */
/*   Updated: 2024/01/15 18:06:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
void	dup_fail(char **args, t_data *data, int fd, t_plist **lst)
{
	perror("Error duplicating file descriptor");
	close(fd);
	close(data->fd_outf);
	close(data->fd_inf);
	fd_closer(0, lst);
	if (args)
		free_array(args);
	if (data->dirs)
		free_array(data->dirs);
	free_list(*lst);
	exit(EXIT_FAILURE);
}

void	fd_fail(char **args, t_data *data, int fd, t_plist **lst)
{
	perror("pipex: file");
	close (fd);
	if (args)
		free_array(args);
	if (data->dirs)
		free_array(data->dirs);
	free_list(*lst);
	exit(EXIT_FAILURE);
}
*/
