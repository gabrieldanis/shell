/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 07:25:06 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:48:34 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*s;

	(void)argc;
	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
		exit(error_message(MALLOC_ERROR, NULL, NULL, s, errno));
	*s = (t_shell){0};
	s->env = dup_envp(envp, s);
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

char	**dup_envp(char **envp, t_shell *s)
{
	char	**dup;
	int	i;

	i = 0;
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
	return (dup);
}
