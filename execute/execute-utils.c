/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:10:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:45:27 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
/*
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
*/

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
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	cmd = ft_strjoin("/", s->tlst->ex->str);
	if (!cmd)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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
/*
void	arg_list(t_shell *s)
{
	t_parsed	*start;
	t_parsed	*sub_start;
	int		i;

	start = s->lst;
	while (s->lst && s->lst->lst)
	{
		s->lst->arglst = (char **)malloc((arglst_size(s->lst) + 1) * sizeof(char *));
		if (!s->lst->arglst)
			free_and_exit(MALLOC_ERROR, s);
		sub_start = s->lst->lst;
		i = 0;
		while (s->lst->lst)
		{
			if (s->lst->lst->type == CMD || s->lst->lst->type == ARG)
			{
				s->lst->arglst[i] = ft_strdup(s->lst->lst->str);
				if (!s->lst->arglst[i])
					free_and_exit(MALLOC_ERROR, s);
				i++;
			}
			s->lst->lst = s->lst->lst->next;
		}
		s->lst->arglst[i] = NULL;
		s->lst->lst = sub_start;
		s->lst = s->lst->next;
	}
	s->lst = start;
}*/
