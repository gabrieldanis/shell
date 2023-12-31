/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/30 22:51:46 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char    *get_path(t_shell *s)
{
    int        i;

    i = 0;
    while (s->env[i] != NULL)
    {
        if (ft_strncmp(s->env[i], "PATH=", 5) == 0)
            return (s->env[i]);
        i++;
    }
    return (NULL);
}

char    *get_dir(char *str, t_shell *s)
{
	char    **dirs;
	char    *dir;
	char    *cmd;
	int        i;

    	dirs = ft_split(str, 58);
	if (!dirs)
		free_and_exit(MALLOC_ERROR, s);
	i = 0;
	cmd = ft_strjoin("/", s->tlst->ex->str);
	if (!cmd)
		free_and_exit(MALLOC_ERROR, s);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dir)
		{
			free(cmd);
			free_and_exit(MALLOC_ERROR, s);
		}
		if (access(dir, F_OK) == 0)
		{
			free_2d_array((void **)dirs);
			free(cmd);
			return (dir);
		}
		free(dir);
		i++;
	}
	free_2d_array((void **)dirs);
	error_message(CMD_ERROR, NULL, cmd + 1);
	free(cmd);
	return (NULL);
}

int	t_lstsize(t_token *list)
{
	int	i;	

	i = 0;
	while (list)
	{
		list = list->next;	
		i++;
	}
	return (i);
}

void	arg_list(t_shell *s)
{
	t_token	*start;
	t_token	*ex_start;
	int		i;

	s->arglst = (char **)malloc((t_lstsize(s->tlst) + 1) * sizeof(char *));
	if (!s->arglst)
			free_and_exit(MALLOC_ERROR, s);
	i = 0;
	start = s->tlst;
	// after improved parsing we will have to set a limit for this while loop
	while (s->tlst)
	{
		ex_start = s->tlst->ex;
		while (s->tlst->ex)
		{
			s->arglst[i] = ft_strdup(s->tlst->ex->str);
			if (!s->arglst[i])
				free_and_exit(MALLOC_ERROR, s);
			s->tlst->ex = s->tlst->ex->next;
			i++;
		}
		s->tlst->ex = ex_start;
		s->tlst = s->tlst->next;
	}
	s->arglst[i] = NULL;
	s->tlst = start;
}

void	exit_child(int n)
{
	error_message(n, NULL, NULL);
	exit(n);
}

void	no_pipe(t_shell *s)
{
	char	*cmd;
	pid_t	pid;
	char	path[500];


	pid = fork();
	if (pid == -1)
			exit_child(FORK_ERROR);
	if (pid == 0)
	{
			cmd = NULL;
			arg_list(s);
		printf("%s\n", s->arglst[0]);
			if (ft_strchr(s->arglst[0], '/'))
			{
				if (s->arglst[0][0] == '.' 
					&& s->arglst[0][1] == '/')
						{
							if (getcwd(path, sizeof(path)) == NULL)
								exit_child(GEN_ERROR);
							cmd = ft_strjoin(path, s->arglst[0] + 1);
						}
				else if (s->arglst[0][0] == '/')
						cmd = s->arglst[0];
				else
						{
							if (getcwd(path, sizeof(path)) == NULL)
								exit_child(GEN_ERROR);
							cmd = ft_strjoin(path, "/");
							cmd = ft_strjoin(cmd, s->arglst[0]);
						}
			}
			else
				cmd = get_dir(get_path(s), s);
			//printf("%s\n", cmd);
			if (!cmd)
				exit_child(CMD_ERROR);
			if (execve(cmd, s->arglst, s->env) == -1)
				exit_child(EXECVE_ERROR);
	}
	else
		wait(NULL);
}

void	execute_parsed_list(t_shell *s)
{
	if (!ft_strncmp(s->tlst->ex->str, "echo\0", 5))
		ft_echo(s->tlst->ex->next);
	else if (!ft_strncmp(s->tlst->ex->str, "exit\0", 5))
		free_and_exit(0, s);
	else if (!ft_strncmp(s->tlst->ex->str, "pwd\0", 4))
		ft_pwd();
	else if (!ft_strncmp(s->tlst->ex->str, "cd\0", 3))
		ft_chdir(s);
	else if (!ft_strncmp(s->tlst->ex->str, "env\0", 4))
		ft_export(s, 1);
	else if (!ft_strncmp(s->tlst->ex->str, "export\0", 7))
		ft_export(s, 0);
	else if (!ft_strncmp(s->tlst->ex->str, "unset\0", 6))
		ft_unset(s);
	else if (!ft_strncmp(s->tlst->ex->str, "clear\0", 6))
		clear_screen();
	else
			no_pipe(s);
}
