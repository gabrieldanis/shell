/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:47:24 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/21 11:09:57 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	malloc_new_env(t_shell *s, char ***tmp, char *str)
{
	int	i;

	i = 0;
	*tmp = s->env;
	while (s->env[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!s->env)
	{
		free(str);
		free_2d_array((void **)*tmp);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
}

void	dup_env_lines(t_shell *s, char *str, char **tmp, int *i)
{
	char	*tmp_str;

	tmp_str = ft_strdup(tmp[*i]);
	if (!tmp_str)
	{
		free(str);
		free_2d_array((void **)tmp);
		free_2d_array_i((void ***)&s->env, *i);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	s->env[*i] = tmp_str;
	(*i)++;
}

void	dup_env_last_line(t_shell *s, char **tmp, int *i)
{
	char	*tmp_str;

	tmp_str = ft_strdup(tmp[(*i) - 1]);
	if (!tmp_str)
	{
		free_2d_array((void **)tmp);
		free_2d_array_i((void ***)&s->env, *i);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	s->env[*i] = tmp_str;
	(*i)++;
}

int	ft_setenv(t_shell *s, char *str)
{
	char	**tmp;
	int		i;

	if (update_existing_var(s, str) || append_var(s, str))
		return (0);
	malloc_new_env(s, &tmp, str);
	i = 0;
	while (tmp[i] && (ft_strncmp(tmp[i], "_=", 2)
			|| (!ft_strncmp(tmp[i], "_=", 2) && tmp[i + 1])))
		dup_env_lines(s, str, tmp, &i);
	s->env[i] = str;
	i++;
	if (tmp [i - 1] && !tmp[i])
		dup_env_last_line(s, tmp, &i);
	s->env[i] = NULL;
	free_2d_array((void **)tmp);
	return (0);
}
