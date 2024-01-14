/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:10:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/14 15:22:51 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_path(t_shell *s)
{
	int	i;

	i = 0;
	while (s->env[i] != NULL)
	{
		if (ft_strncmp(s->env[i], "PATH=", 5) == 0)
			return (s->env[i]);
		i++;
	}
	return (NULL);
}

char	*find_dir(t_shell *s, char *cmd, char **dirs)
{
	char	*dir;
	int		i;

	i = 0;
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dir)
		{
			free(cmd);
			free_2d_array((void **)dirs);
			free_and_exit(MALLOC_ERROR, s);
		}
		if (access(dir, F_OK) == 0)
		{
			free_2d_array((void **)dirs);
			free(cmd);
			return (dir);
		}
		free(dir);
		i++;
	}
	return (NULL);
}

char	*get_dir(char *str, t_shell *s)
{
	char	**dirs;
	char	*cmd;
	char	*dir;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_and_exit(MALLOC_ERROR, s);
	cmd = ft_strjoin("/", s->tlst->ex->str);
	if (!cmd)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s);
	}
	dir = find_dir(s, cmd, dirs);
	if (dir)
		return (dir);
	free_2d_array((void **)dirs);
	error_message(CMD_ERROR, NULL, cmd + 1, s);
	free(cmd);
	return (NULL);
}

int	t_lstsize(t_token *list)
{
	int	i;	

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	exit_child(int n, t_shell *s)
{
	error_message(n, NULL, NULL, s);
	exit(0);
}
