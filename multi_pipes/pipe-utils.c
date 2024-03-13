/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:01:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/09 11:19:21 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_dir_multi(t_shell *s)
{
	t_parsed	*node;
	char		**dirs;
	char		*dir;
	char		*cmd;
	char		*tmp;		
	int			i;

	dirs = NULL;
	if(s->path)
	{
		dirs = ft_split(s->path, 58);
		if (!dirs)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		tmp = ft_strdup(ft_strchr(dirs[0], '=') + 1);
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		free(dirs[0]);
		dirs[0] = tmp;
	}
	node = s->lst;
	while (node)
	{
		if (node->arglst && node->arglst[0] && dirs)
		{
			i = 0;
			if (ft_strchr(node->arglst[0], '/'))
			{
				if(access(node->arglst[0], F_OK) == 0)
					node->cmd_found = 1;
				node->cmd = ft_strdup(node->arglst[0]);
				if (!node->cmd)
					free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			}
			else if (node->arglst[0][0] != '\0')
			{
				cmd = ft_strjoin("/", node->arglst[0]);
				if (!cmd)
					free_and_exit(MALLOC_ERROR, s, NULL, NULL);
				while (dirs[i] != NULL)
				{
					dir = ft_strjoin(dirs[i], cmd);
					if (!dir)
						free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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
		}
		if (!node->cmd && node->arglst && node->arglst[0])
		{
			node->cmd_found = 0;
			if(access(node->arglst[0], F_OK) == 0 && !s->path)
				node->cmd_found = 1;
			node->cmd = ft_strdup(node->arglst[0]);
			if (!node->cmd)
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		}
		node = node->next;
	}
	if (dirs)
		free_2d_array((void **)dirs);
	return (0);
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
	while (i < ind)
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
