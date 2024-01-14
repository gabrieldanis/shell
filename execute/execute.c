/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/14 14:53:16 by gdanis           ###   ########.fr       */
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
		no_pipe(s);
}

void	no_pipe(t_shell *s)
{
	pid_t	pid;
	char	*cmd;
	char	path[500];
	int		status;

	pid = fork();
	if (pid == -1)
		exit_child(FORK_ERROR, s);
	if (pid == 0)
	{
		cmd = NULL;
		if (ft_strchr(s->lst->arglst[0], '/'))
		{
			if (s->lst->arglst[0][0] == '.'
				&& s->lst->arglst[0][1] == '/')
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR, s);
				cmd = ft_strjoin(path, s->lst->arglst[0] + 1);
			}
			else if (s->lst->arglst[0][0] == '/')
				cmd = s->lst->arglst[0];
			else
			{
				if (getcwd(path, sizeof(path)) == NULL)
					exit_child(GEN_ERROR, s);
				cmd = ft_strjoin(path, "/");
				cmd = ft_strjoin(cmd, s->lst->arglst[0]);
			}
		}
		else
			cmd = get_dir(get_path(s), s);
		if (!cmd)
			exit(1);
		if (execve(cmd, s->lst->arglst, s->env) == -1)
			exit_child(EXECVE_ERROR, s);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			s->rval = WEXITSTATUS(status);
	}
}
