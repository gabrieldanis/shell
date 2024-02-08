/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 13:46:16 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute(t_shell *s)
{
	if(s->cmds == 1)
	{
		if (execute_builtin(s))	
			return ;
	}
	multi_pipe(s);
}

int	execute_builtin(t_shell *s)

{
	if (!ft_strncmp(s->lst->arglst[0], "echo\0", 5))
		return (s->rval = ft_echo(s->lst), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "exit\0", 5))
		return (ft_exit(s, s->lst), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "pwd\0", 4))
		return (s->rval = ft_pwd(s), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "cd\0", 3))
		return (ft_chdir(s, s->lst), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "env\0", 4))
		return (s->rval = ft_export(s, s->lst, 1), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "export\0", 7))
		return (s->rval = ft_export(s, s->lst, 0), 1);
	else if (!ft_strncmp(s->lst->arglst[0], "unset\0", 6))
		return (s->rval = ft_unset(s, s->lst), 1);
	return (0);
}
