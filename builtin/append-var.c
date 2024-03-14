/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append-var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:48:48 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:43:27 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	append_var(t_shell *s, char *str)
{
	char	*tmp;
	char	*tmp_join;
	char	**split_str;
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
			{
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
			if (!ft_strncmp(s->env[i], str, len)
				&& s->env[i][len] == '\0')
			{
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
			i++;
		}
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
	return (0);
}

