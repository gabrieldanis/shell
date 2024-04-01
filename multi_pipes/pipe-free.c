/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:08:13 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/01 11:14:24 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_list(t_parsed *lst)
{
	t_parsed	*current;
	t_parsed	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	create_outfiles(t_shell *s)
{
	t_parsed	*node;
	int			i;

	node = s->lst;
	while (node)
	{
		i = 0;
		while (node->outfiles && node->outfiles[i])
		{
			if (!check_outfile_access(node->outfiles[i],
					node->outfiles[i + 1], s))
				return (0);
			i++;
		}
		node = node->next;
	}
	return (1);
}

int	check_outfile_access(char *str, char *str2, t_shell *s)
{
	int	old;

	if (access(str, F_OK) == 0
		&& access(str, W_OK) != 0
		&& str2)
		return (error_message(OUTFILE_ERROR, NULL, str, s), 0);
	if (str2)
	{
		old = open(str, O_WRONLY | O_TRUNC
				| O_CREAT, 0644);
		if (old == -1 && (!(access(str, F_OK) == 0
					&& access(str, W_OK) != 0
					&& str2)))
			return (error_message(OUTFILE_ERROR, NULL, str, s), 0);
	}
	else
	{
		old = open(str, O_WRONLY | O_CREAT, 0664);
		if (old == -1)
			return (error_message(OUTFILE_ERROR, NULL, str, s), 0);
	}
	close(old);
	return (1);
}

void	free_cmd_dirs(t_shell *s, char **dirs, char *cmd)
{
	free(cmd);
	free_2d_array((void **)dirs);
	free_and_exit(MALLOC_ERROR, s, NULL, NULL);
}
