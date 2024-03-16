/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append-var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:48:48 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/16 11:43:16 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	env_i_has_equal_sign(t_shell *s, char *str, int len, int i)
{
	char	*tmp;
	char	*tmp_join;

	if (str[len + 2])
	{
		tmp = s->env[i];
		tmp_join = ft_strjoin(s->env[i], str + len + 2);
		if (!tmp_join)
		{
			free(str);
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		}
		s->env[i] = tmp_join;
		free(tmp);
	}
	free(str);
	return (1);
}

int	env_i_no_equal_sign(t_shell *s, char *str, int len, int i)
{
	char	*tmp;
	char	*tmp_join;

	tmp = s->env[i];
	tmp_join = ft_strjoin(s->env[i], "=");
	if (!tmp_join)
	{
		free(str);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	s->env[i] = tmp_join;
	tmp_join = ft_strjoin(s->env[i], str + len + 2);
	if (!tmp_join)
	{
		free(str);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	s->env[i] = tmp_join;
	free(tmp);
	free(str);
	return (1);
}

int	create_new_env_i(t_shell *s, char *str)
{
	char	**split_str;
	char	*tmp;

	split_str = ft_split(str, '+');
	if (!split_str)
	{
		free(str);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	tmp = ft_strjoin(split_str[0], split_str[1]);
	if (!tmp)
	{
		free(str);
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	ft_setenv(s, tmp);
	free_2d_array((void **)split_str);
	free(str);
	return (1);
}

int	append_var(t_shell *s, char *str)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (str[len] == '+' && str[len + 1] && str[len + 1] == '=')
	{
		while (s->env[i])
		{
			if (!ft_strncmp(s->env[i], str, len)
				&& s->env[i][len] == '=')
				return (env_i_has_equal_sign(s, str, len, i));
			if (!ft_strncmp(s->env[i], str, len)
				&& s->env[i][len] == '\0')
				return (env_i_no_equal_sign(s, str, len, i));
			i++;
		}
		return (create_new_env_i(s, str));
	}
	return (0);
}
