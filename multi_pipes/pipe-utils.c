/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:01:22 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 14:24:31 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_dir_multi(t_shell *s)
{
	t_parsed	*node;
	char		**dirs;	

	dirs = NULL;
	if (s->path)
		dirs = get_dirs(s, dirs);
	node = s->lst;
	while (node)
	{
		if (node->arglst && node->arglst[0] && dirs)
			check_arglst(s, node, dirs);
		if (!node->cmd && node->arglst && node->arglst[0])
		{
			node->cmd_found = 0;
			if (access(node->arglst[0], F_OK) == 0 && !s->path)
				node->cmd_found = 1;
			node->cmd = ft_strdup(node->arglst[0]);
			check_cmd(s, dirs, node);
		}
		node = node->next;
	}
	if (dirs)
		free_2d_array((void **)dirs);
	return (0);
}

void	check_cmd(t_shell *s, char **dirs, t_parsed *node)
{
	if (!node->cmd)
	{
		free_2d_array((void **)dirs);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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
