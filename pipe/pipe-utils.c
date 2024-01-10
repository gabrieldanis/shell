/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:43:35 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/10 08:45:40 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_path(t_shell *s)
{
	int        i;

	i = 0;
	while (s->env[i] != NULL)
	{
		if (ft_strncmp(s->env[i], "PATH=", 5) == 0)
			return (s->env[i]);
		i++;
	}
	return (NULL);
}

char	*get_dir(char *str, t_shell *s)
{
	char    **dirs;
	char    *dir;
	char    *cmd;
	int        i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_and_exit(MALLOC_ERROR, s);
	i = 0;
	cmd = ft_strjoin("/", s->lst->arglst[0]);
	if (!cmd)
		free_and_exit(MALLOC_ERROR, s);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dir)
		{
			free(cmd);
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

void	add_path_to_cmd(t_shell *s)
{
	t_parsed	*start;
	char		*tmp;
	char		path[500];

	start = s->lst;
	while (s->lst)
	{
		if (s->lst->arglst[0] && ft_strchr(s->lst->arglst[0], '/'))
		{
			if (s->lst->arglst[0][0] == '.' 
				&& s->lst->arglst[0][1] == '/')
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR, s);
				s->lst->cmd = ft_strjoin(path, s->lst->arglst[0] + 1);
				if (!s->lst->cmd)
					free_and_exit(MALLOC_ERROR, s);
			}
			else if (s->lst->arglst[0][0] == '/')
					s->lst->cmd = s->lst->arglst[0];
			else
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR, s);
				tmp = ft_strjoin(path, "/");
				if (!tmp)
					free_and_exit(MALLOC_ERROR, s);
				s->lst->cmd = ft_strjoin(tmp, s->lst->arglst[0]);
				if (!s->lst->cmd)
					free_and_exit(MALLOC_ERROR, s);
				free(tmp);
			}
		}
		else if (s->lst->arglst[0] && !check_builtin(s->lst))
			s->lst->cmd = get_dir(get_path(s), s);
		s->lst = s->lst->next;
	}
	s->lst = start;
}
