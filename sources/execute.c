/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:08:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/26 12:22:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


char    *get_path(char **env)
{
    int        i;

    i = 0;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i]);
        i++;
    }
    return (NULL);
}

char    *get_dir(char *str, char *cmd)
{
    char    **dirs;
    char    *dir;
    int        i;

    dirs = ft_split(str, 58);
	if (!dirs)
			free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
    i = 0;
    cmd = ft_strjoin("/", cmd);
    while (dirs[i] != NULL)
    {
        dir = ft_strjoin(dirs[i], cmd);
        if (access(dir, F_OK) == 0)
        {
            free_2d_array((void **)dirs);
            return (dir);
        }
        i++;
    }
    free_2d_array((void **)dirs);
	error_message(CMD_ERROR, NULL, cmd + 1);
    return (NULL);
}

int	p_lstsize(t_parsed *list)
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

char	**arg_list(t_parsed *plist)
{
	char	*str;
	char **list;
	int	i;

	list = (char **)malloc((p_lstsize(plist) + 1) * sizeof(char *));
	if (!list)
			free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	i = 0;
	while (plist)
	{
		if (plist->expand)
			str = plist->expand;
		else
			str = plist->str;
		list[i] = ft_strdup(str);
		if (!list[i])
			free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
		plist = plist->next;
		i++;
	}
	return (list);
}

void	execute_parsed_list(t_parsed *plist, char ***envp, t_token *list)
{
	char	*cmd;
	char	**args;

	args = arg_list(plist);
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
		cmd = get_dir(get_path(*envp), cmd);
		if (!cmd)
				return;
		if (execve(cmd, args, *envp) == -1)
		{
				printf("hi\n");
				free_and_exit(EXECVE_ERROR, NULL, NULL, NULL);
		}
		printf("i found command in path %s\n", get_dir(get_path(*envp), cmd));
		/*
		printf("command unknown\n");
		print_parsed_list(plist);
		*/
	}
}
