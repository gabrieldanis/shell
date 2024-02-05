/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/05 11:22:55 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_shell *s)
{
	if (!ft_strncmp(s->lst->arglst[0], "echo\0", 5))
		s->rval = ft_echo(s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "exit\0", 5))
		ft_exit(s, s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "pwd\0", 4))
		s->rval = ft_pwd(s);
	else if (!ft_strncmp(s->lst->arglst[0], "cd\0", 3))
		ft_chdir(s, s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "env\0", 4))
		s->rval = ft_export(s, s->lst, 1);
	else if (!ft_strncmp(s->lst->arglst[0], "export\0", 7))
		s->rval = ft_export(s, s->lst, 0);
	else if (!ft_strncmp(s->lst->arglst[0], "unset\0", 6))
		s->rval = ft_unset(s, s->lst);
	else
		multi_pipe(s);
}
