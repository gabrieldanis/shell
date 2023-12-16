/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/16 15:35:15 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_parsed *list, char **envp)
{
	if (!ft_strncmp(list->str, "echo\0", 5))
		ft_echo(list->next);
	else if (!ft_strncmp(list->str, "exit\0", 5))
		ft_exit(list->next);
	else if (!ft_strncmp(list->str, "pwd\0", 4))
		ft_pwd();
	else if (!ft_strncmp(list->str, "cd\0", 3))
		ft_chdir(list);
	else if (!ft_strncmp(list->str, "env\0", 4))
		ft_env(envp);
	else if (!ft_strncmp(list->str, "export\0", 7))
		ft_export(envp, list);
	else
	{
		printf("command unknown\n");
		print_parsed_list(list);
	}
}
