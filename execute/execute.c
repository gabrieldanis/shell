/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/10 08:31:47 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_builtin(t_shell *s, t_parsed *lst)
{
	if (!ft_strncmp(lst->arglst[0], "echo\0", 5))
		ft_echo(s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "exit\0", 5))
		ft_exit(s, lst);
	else if (!ft_strncmp(lst->arglst[0], "pwd\0", 4))
		ft_pwd(s);
	else if (!ft_strncmp(lst->arglst[0], "cd\0", 3))
		ft_chdir(s, s->lst);
	else if (!ft_strncmp(lst->arglst[0], "env\0", 4))
		ft_export(s, s->lst, 1);
	else if (!ft_strncmp(lst->arglst[0], "export\0", 7))
		ft_export(s, s->lst, 0);
	else if (!ft_strncmp(lst->arglst[0], "unset\0", 6))
		ft_unset(s, s->lst);
}

int	check_builtin(t_parsed *lst)
{
	if (!ft_strncmp(lst->arglst[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "exit\0", 5))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(lst->arglst[0], "unset\0", 6))
		return (1);
	return (0);
}
