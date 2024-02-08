/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:47:24 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:44:45 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_setenv(t_shell *s, char *str)
{
	char	**tmp;
	char	*tmp_str;
	int		i;

	if (update_existing_var(s, str))
		return (0);
	if (append_var(s, str))
		return (0);
	i = 0;
	tmp = s->env;
	while (s->env[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!s->env)
	{
		free(str);
		free_2d_array((void **)tmp);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "_=", 2))
	{
		tmp_str = ft_strdup(tmp[i]);
		if (!tmp_str)
		{
			free(str);
			free_2d_array((void **)tmp);
			free_2d_array_i((void ***)&s->env, i);
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		}
		s->env[i] = tmp_str;
		i++;
	}
	s->env[i] = str;
	i++;
	tmp_str = ft_strdup(tmp[i - 1]);
	if (!tmp_str)
	{
		free_2d_array((void **)tmp);
		free_2d_array_i((void ***)&s->env, i);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	s->env[i] = tmp_str;
	i++;
	s->env[i] = NULL;
	free_2d_array((void **)tmp);
	return (0);
}
