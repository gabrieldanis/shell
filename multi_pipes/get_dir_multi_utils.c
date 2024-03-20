/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_multi_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:49:52 by dberes            #+#    #+#             */
/*   Updated: 2024/03/20 09:50:04 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_dirs(t_shell *s, char **dirs)
{
	char		*tmp;

	dirs = ft_split(s->path, 58);
	if (!dirs)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	tmp = ft_strdup(ft_strchr(dirs[0], '=') + 1);
	if (!tmp)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	free(dirs[0]);
	dirs[0] = tmp;
	return (dirs);
}

void	check_arglst(t_shell *s, t_parsed *node, char **dirs)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strchr(node->arglst[0], '/'))
		check_absolute_path(s, node, dirs);
	else if (node->arglst[0][0] != '\0')
	{
		cmd = join_slash(s, node, dirs, cmd);
		check_for_dir(s, node, dirs, cmd);
	}
}

void	check_absolute_path(t_shell *s, t_parsed *node, char **dirs)
{
	if (access(node->arglst[0], F_OK) == 0)
		node->cmd_found = 1;
	node->cmd = ft_strdup(node->arglst[0]);
	if (!node->cmd)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
}

char	*join_slash(t_shell *s, t_parsed *node, char **dirs, char *cmd)
{
	cmd = ft_strjoin("/", node->arglst[0]);
	if (!cmd)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	return (cmd);
}

void	check_for_dir(t_shell *s, t_parsed *node, char **dirs, char *cmd)
{
	int		i;
	char	*dir;

	i = 0;
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dir)
			free_cmd_dirs(s, dirs, cmd);
		if (access(dir, F_OK) == 0)
		{
			node->cmd = dir;
			node->cmd_found = 1;
			free(cmd);
			cmd = NULL;
			break ;
		}
		else
			free (dir);
		i++;
	}
	if (cmd)
		free (cmd);
}
