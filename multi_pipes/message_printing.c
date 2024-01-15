/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:43:22 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 14:39:34 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	dirs_calloc(t_data *data)
{
	data->dirs = (char **)ft_calloc(sizeof(char *), (data->argc - 2));
	if (data->dirs == NULL)
	{
		ft_printf("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void	dup_fail(char **args, t_data *data, int fd, int fd_file)
{
	perror("Error duplicating file descriptor");
	close(fd);
	close(fd_file);
	if (args)
		free_array(args);
	if (data->dirs)
		free_dirs(data->dirs);
	exit(EXIT_FAILURE);
}
