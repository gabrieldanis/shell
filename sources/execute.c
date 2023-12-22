/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/22 15:55:44 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_parsed *plist, char ***envp, t_token *list)
{
	char	*cmd;

	if (plist->expand)
		cmd = plist->expand;
	else
		cmd = plist->str;
	if (!ft_strncmp(cmd, "echo\0", 5))
		ft_echo(plist->next);
	else if (!ft_strncmp(cmd, "exit\0", 5))
		free_and_exit(0, list, plist, *envp);
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd, "cd\0", 3))
		ft_chdir(plist,envp);
	else if (!ft_strncmp(cmd, "env\0", 4))
		ft_export(envp, plist, 1);
	else if (!ft_strncmp(cmd, "export\0", 7))
		ft_export(envp, plist, 0);
	else if (!ft_strncmp(cmd, "unset\0", 6))
		ft_unset(envp, plist);
	else if (!ft_strncmp(cmd, "clear\0", 6))
		clear_screen();
	else
	{
		printf("command unknown\n");
		print_parsed_list(plist);
	}
}
