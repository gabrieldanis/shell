/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:10:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/05 18:07:56 by gdanis           ###   ########.fr       */
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
	cmd = ft_strjoin("/", s->tlst->ex->str);
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

int	arglst_size(t_parsed *lst)
{
	t_parsed	*sub_start;
	int			i;

	i = 0;
	sub_start = lst->lst;
	while (lst->lst)
	{
		if (lst->lst->type == CMD || lst->lst->type == ARG)
			i++;
		lst->lst = lst->lst->next;
	}
	lst->lst = sub_start;
	return (i);
}

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
}

void	exit_child(int n, t_shell *s)
{
	error_message(n, NULL, NULL, s);
	exit(n);
}
