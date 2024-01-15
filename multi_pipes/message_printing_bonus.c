/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:55:12 by dberes            #+#    #+#             */
/*   Updated: 2024/01/15 16:03:50 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*result;
	char	*tmp;

	if (!str1)
		return (NULL);
	if (!str2)
		return (ft_strdup(str1));
	tmp = ft_strjoin(str1, str2);
	if (!tmp)
		return (NULL);
	if (!str3)
		return (tmp);
	result = ft_strjoin(tmp, str3);
	free(tmp);
	return (result);
}

char	*get_path(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
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
