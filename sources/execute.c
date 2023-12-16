/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/16 17:21:05 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_parsed *list, char **envp)
{
	char	*cmd;

	if (list->expand)
		cmd = list->expand;
	else
		cmd = list->str;
	if (!ft_strncmp(cmd, "echo\0", 5))
		ft_echo(list->next);
	else if (!ft_strncmp(cmd, "exit\0", 5))
		ft_exit(list->next);
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd, "cd\0", 3))
		ft_chdir(list);
	else if (!ft_strncmp(cmd, "env\0", 4))
		ft_export(envp, list, 1);
	else if (!ft_strncmp(cmd, "export\0", 7))
		ft_export(envp, list, 0);
	else
	{
		printf("command unknown\n");
		print_parsed_list(list);
	}
}
