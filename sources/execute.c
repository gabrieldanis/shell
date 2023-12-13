/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/13 20:21:31 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_parsed *list)
{
	if (!ft_strncmp(list->str, "echo\0", 5))
	{
		printf("echo recognized\n");
		//ft_echo(list);
	}
	else
	{
		printf("command unknown\n");
		print_parsed_list(list);
	}
	

}
