/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 07:25:06 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 10:54:25 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	set_shell(t_shell *s)
{
	char	*str;
	char	*old;

	str = ft_strjoin("SHELL=", s->argv[0]);
	if (!str)
		free_and_exit(MALLOC_ERROR, s);
	old = str;
	str = ft_strjoin(str, " has taken over 💩 💩 💩");
	free(old);
	if (!str)
		free_and_exit(MALLOC_ERROR, s);
	ft_setenv(s, str);
	free(str);
}

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*s;

	(void)argc;
	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
	{
		error_message(MALLOC_ERROR, NULL, NULL);
		exit(0);
	}
	*s = (t_shell){0};
	s->env = dup_envp(envp);
	s->argv = argv;
	set_shell(s); // not necessary
	set_shlvl(s);
	ft_signal(s);
	s->str = NULL;
	return (s);
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
					free_and_exit(MALLOC_ERROR, s);
				tmp = ft_strjoin("SHLVL=", num);
				free(num);
				if (!tmp)
					free_and_exit(MALLOC_ERROR, s);
				ft_setenv(s, tmp);
				checker = 1;
				free(tmp);
		}
		i++;
	}
	if (!checker)
		ft_setenv(s, "SHLVL=1");
}

char	**dup_envp(char **envp)
{
	char	**dup;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		free_and_exit(MALLOC_ERROR, NULL);
	i = 0;
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
