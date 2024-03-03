/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/03 13:25:00 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute(t_shell *s)
{
	int	original_stdout;
	int	original_stdin;

	//parse_lstiter(s, parse_heredoc);
	if(s->cmds == 1)
	{
		if (s->lst->infile)
		{
			original_stdin = dup(0);
			fd_opener(s->lst, s);
		}
		if (s->lst->outfiles)
		{
			ft_write_to_file(s, s->lst);
			original_stdout = dup(1);
		}
		if (execute_builtin(s, s->lst))
		{
			if (s->lst->outfiles)
			{
				dup2(original_stdout, 1);
				close(original_stdout);
			}
			if (s->lst->infile)
			{
				dup2(original_stdin, 0);
				close(original_stdin);
			}
			return ;
		}
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
