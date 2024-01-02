/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 11:13:40 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_parsed_list(t_shell *s)
{
	if (!ft_strncmp(s->lst->arglst[0], "echo\0", 5))
		s->rval = ft_echo(s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "exit\0", 5))
		free_and_exit(0, s);
	else if (!ft_strncmp(s->lst->arglst[0], "pwd\0", 4))
		s->rval = ft_pwd();
	else if (!ft_strncmp(s->lst->arglst[0], "cd\0", 3))
		s->rval = ft_chdir(s, s->lst);
	else if (!ft_strncmp(s->lst->arglst[0], "env\0", 4))
		s->rval = ft_export(s, s->lst, 1);
	else if (!ft_strncmp(s->lst->arglst[0], "export\0", 7))
		s->rval = ft_export(s, s->lst, 0);
	else if (!ft_strncmp(s->lst->arglst[0], "unset\0", 6))
		s->rval = ft_unset(s, s->lst);
	else
		no_pipe(s);
}

void	no_pipe(t_shell *s)
{
	pid_t	pid;
	char	*cmd;
	char	path[500];


	pid = fork();
	if (pid == -1)
		exit_child(FORK_ERROR);
	if (pid == 0)
	{
		cmd = NULL;
		if (ft_strchr(s->lst->arglst[0], '/'))
		{
			if (s->lst->arglst[0][0] == '.' 
				&& s->lst->arglst[0][1] == '/')
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR);
				cmd = ft_strjoin(path, s->lst->arglst[0] + 1);
			}
			else if (s->lst->arglst[0][0] == '/')
					cmd = s->lst->arglst[0];
			else
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR);
				cmd = ft_strjoin(path, "/");
				cmd = ft_strjoin(cmd, s->lst->arglst[0]);
			}
		}
		else
			cmd = get_dir(get_path(s), s);
		if (!cmd)
			exit_child(CMD_ERROR);
		s->rval = execve(cmd, s->lst->arglst, s->env);
		if ( s->rval == -1)
			exit_child(EXECVE_ERROR);
	}
	else
		wait(NULL);
}
