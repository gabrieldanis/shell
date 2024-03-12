/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 07:25:06 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/12 10:51:03 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*s;

	//print_env(envp);
	(void)argc;
	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		exit(error_message(MALLOC_ERROR, NULL, NULL, s, errno));
	*s = (t_shell){0};
	s->env = dup_envp(envp, s);
	//print_env(s->env);
	s->argv = argv;
	//set_shell(s); // not necessary
	//print_env(s->env);
	set_shlvl(s);
	//print_env(s->env);
	ft_signal(s);
	s->str = NULL;
	return (s);
}

void	set_shell(t_shell *s)
{
	char	*str;
	char	*old;

	str = ft_strjoin("SHELL=", s->argv[0]);
	if (!str)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	old = str;
	str = ft_strjoin(str, " has taken over 💩 💩 💩");
	free(old);
	if (!str)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	ft_setenv(s, str);
}

void	set_shlvl(t_shell *s)
{
	char	*tmp;
	char	*num;
	int		i;
	int		checker;

	i = 0;
	checker = 0;
	while (s->env[i])
	{
		if (!strncmp(s->env[i], "SHLVL=", 6))	
		{
				num = ft_itoa(ft_atoi(ft_strchr(s->env[i], '=') + 1) + 1);
				if (!num)
					free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
				tmp = ft_strjoin("SHLVL=", num);
				free(num);
				if (!tmp)
					free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
				ft_setenv(s, tmp);
				checker = 1;
		}
		i++;
	}
	if (!checker)
	{
		tmp = ft_strdup("SHLVL=1");
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
		ft_setenv(s, tmp);
	}
}

char **create_environment(t_shell *s)
{
	char 	**env;
	char	path[500];
	char	*path_var;

	if (getcwd(path, sizeof(path)) == NULL)
		error_message(GEN_ERROR, "pwd", NULL, s, errno);
	path_var = ft_strjoin("PWD=", path);
	if (!path_var)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	env = (char **)malloc(sizeof(char *) * (4));
	if (!env)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	env[0] = ft_strdup("OLDPWD");
	if (!env[0])
	{
		free_2d_array((void **)env);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	}
	env[1] = path_var;
	env[2] = ft_strdup("_=/usr/bin/env");
	if (!env[2])
	{
		free_2d_array((void **)env);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	}
	env[3] = NULL;
	return (env);
}

char	**dup_envp(char **envp, t_shell *s)
{
	char	**dup;
	int	i;

	i = 0;
	if (!envp[0])
		dup = create_environment(s);
	else
	{
		while (envp[i])
			i++;
		dup = (char **)malloc(sizeof(char *) * (i + 1));
		if (!dup)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
		i = 0;
		while (envp[i])
		{
			dup[i] = ft_strdup(envp[i]);
			if (!dup[i])
			{
				free_2d_array_i((void ***)&dup, i);
				free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
			}
			i++;
		}
		dup[i] = NULL;
	}
	return (dup);
}
