/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:08:13 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/05 11:31:01 by dberes           ###   ########.fr       */
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
/*
void	free_exit(char **args, t_data *data, char **dirs, int ex_code)
{
	if (ex_code == 1)
	{
		free_array(data->dirs);
		free_array(args);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 2)
	{
		if (data && data->dirs)
			free_array(data->dirs);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 4)
	{
		if (dirs)
			free_array(dirs);
		if (data && data->dirs)
			free_array(data->dirs);
		if (args)
			free_array(args);
		printf("malloc failed");
		exit(EXIT_FAILURE);
	}
}*/

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
