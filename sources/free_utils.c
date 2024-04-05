/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:12:03 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/05 10:39:42 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_2d_array(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			if (ptr[i])
				free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

void	free_2d_array_i(void ***arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free((*arr)[j++]);
	free(*arr);
	*arr = NULL;
}

void	delete_files(t_shell *s)
{
	t_parsed	*node;
	t_parsed	*parent_node;

	parent_node = s->lst;
	while (parent_node)
	{
		node = parent_node->lst;
		while (node)
		{
			if (node->type == HEREDOC && node->filename
					&& !access(node->filename, F_OK))
			{
				if (unlink(node->filename) == -1)
					free_and_exit(UNLINK_ERROR, s, NULL, NULL);
			}
			node = node->next;
		}
		parent_node = parent_node->next;
	}
}

void	free_s_str(t_shell *s)
{
	if (s->str)
	{
		free(s->str);
		s->str = NULL;
	}
}

void	free_parsed_list_strings(t_parsed *tmp)
{
	if (tmp->str)
	{
		free(tmp->str);
		tmp->str = NULL;
	}
	if (tmp->filename)
		free (tmp->filename);
	if (tmp->cmd)
		free (tmp->cmd);
}
