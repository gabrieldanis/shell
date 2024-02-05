/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:01:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/05 12:28:23 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*get_dir_multi(t_shell *s)
{
	t_parsed	*node;
	char		**dirs;
	char		*dir;
	char		*cmd;
	int			i;

	dirs = ft_split(s->path, 58);
	if (!dirs)
		free_and_exit(MALLOC_ERROR, s);
	node = s->lst;
	while (node)
	{
		i = 0;
		cmd = ft_strjoin("/", s->lst->arglst[0]);
		if (!cmd)
			free_and_exit(MALLOC_ERROR, s);
		while (dirs[i] != NULL)
		{
			dir = ft_strjoin(dirs[i], cmd);
			if (!dir)
				free_and_exit(MALLOC_ERROR, s);
			if (access(dir, F_OK) == 0)
			{
				node->cmd = dir;
				free(cmd);
				free_2d_array((void **)dirs);
				return (dir);
			}
			free (dir);
			i++;
		}
		/*return (free(cmd), free_array(dirs), NULL);*/
		node = node->next;
	}
	return (NULL);
}

/*
 *
 *
 *
 * need to finish dir_copy. maybe multipipe works then
 *
 *
 */

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
			directory = get_dir_multi(s);
			if (directory == NULL)
			{
				printf("pipex: %s: command not found\n", node->arglst[0]);
				*ex = 1;
			}
			else if (*ex == 0)
				node->dirs[i - 2] = ft_strdup(directory);
			free(directory);
		}
		node = node->next;
	}
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

void	count_parsed_nodes(t_shell *s)
{
	t_parsed *start;

	s->cmds = 0;
	start = s->lst;
	while (s->lst)
	{
		s->cmds++;
		s->lst = s->lst->next;	
	}
	s->lst = start;
}


t_parsed	*get_to_node(t_parsed *node, int ind)
{
	int	i;

	i = 0;
	// should this - 1 still be here?
	while (i < ind - 1)
	{
		node = node->next;
		i++;
	}
	return (node);
}

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
