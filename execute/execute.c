/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/04 10:34:33 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute(t_shell *s)
{
	int	original_stdout;
	int	original_stdin;

	//parse_lstiter(s, parse_heredoc);
	if(s->cmds == 1 && s->lst->arglst && s->lst->arglst[0] && check_builtin(s->lst->arglst[0]))
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

int	check_builtin(char *str)
{
	if (!ft_strncmp(str, "echo\0", 5))
		return (1);
	if (!ft_strncmp(str, "exit\0", 5))
		return (1);
	if (!ft_strncmp(str, "pwd\0", 4))
		return (1);
	if (!ft_strncmp(str, "cd\0", 3))
		return (1);
	if (!ft_strncmp(str, "env\0", 4))
		return (1);
	if (!ft_strncmp(str, "export\0", 7))
		return (1);
	if (!ft_strncmp(str, "unset\0", 6))
		return (1);
	return (0);
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
