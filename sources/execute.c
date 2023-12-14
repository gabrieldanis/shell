/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/14 15:48:38 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_parsed *list)
{
	if (!ft_strncmp(list->str, "echo\0", 5))
		ft_echo(list->next);
	if (!ft_strncmp(list->str, "exit\0", 5))
		ft_exit(list->next);
	if (!ft_strncmp(list->str, "pwd\0", 4))
		ft_pwd();
	else
	{
		printf("command unknown\n");
		print_parsed_list(list);
	}
	

}
