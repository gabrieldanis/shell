/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/09 16:19:07 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute(t_shell *s)
{
	//parse_lstiter(s, parse_heredoc);
	if(s->cmds == 1)
	{
		if (execute_builtin(s, s->lst))
			return ;
	}
	multi_pipe(s);
}

int	execute_builtin(t_shell *s, t_parsed *node)

{
	if (!ft_strncmp(node->arglst[0], "echo\0", 5))
		return (s->rval = ft_echo(node), 1);
	if (!ft_strncmp(node->arglst[0], "exit\0", 5))
		return (ft_exit(s, node), 1);
	if (!ft_strncmp(node->arglst[0], "pwd\0", 4))
		return (s->rval = ft_pwd(s), 1);
	if (!ft_strncmp(node->arglst[0], "cd\0", 3))
		return (ft_chdir(s, node), 1);
	if (!ft_strncmp(node->arglst[0], "env\0", 4))
		return (s->rval = ft_export(s, node, 1), 1);
	if (!ft_strncmp(node->arglst[0], "export\0", 7))
		return (s->rval = ft_export(s, node, 0), 1);
	if (!ft_strncmp(node->arglst[0], "unset\0", 6))
		return (s->rval = ft_unset(s, node), 1);
	return (0);
}
