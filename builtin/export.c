/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/14 20:51:43 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_export(t_shell *s, t_parsed *lst, int env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (env)
		return (ft_env(s), 0);
	if (!lst->arglst[1])
		return (ft_print_export(s->env, s), 0);
	i++;
	while (lst->arglst[i])
	{
		if (!is_varname(lst->arglst[i]))
			return (error_message(IDENT_ERROR, "export", lst->arglst[i], s), 1);
		tmp = ft_strdup(lst->arglst[i]);
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s);
		if (ft_setenv(s, tmp))
			return (1);
		i++;
	}
	return (0);
}

int	update_existing_var(t_shell *s, char *str)
{
	char	*tmp;
	int		i;
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	i = 0;
	while (s->env[i])
	{
		if (!ft_strncmp(s->env[i], str, len)
			&& (s->env[i][len] == '=' || s->env[i][len] == '\0'))
		{
			if (str[len] == '\0')
				return (1);
			tmp = s->env[i];
			s->env[i] = str;
			free(tmp);
 			return (1);
		}
		i++;
	}
	return (0);
}

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
						free_and_exit(MALLOC_ERROR, s);
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
					free_and_exit(MALLOC_ERROR, s);
				}
				s->env[i] = tmp_join;
				tmp_join = ft_strjoin(s->env[i], str + len + 2);
				if (!tmp_join)
				{
					free(str);
					free_and_exit(MALLOC_ERROR, s);
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
			free_and_exit(MALLOC_ERROR, s);
		}
		tmp = ft_strjoin(split_str[0], split_str[1]);
		if (!tmp)
		{
			free(str);
			free_and_exit(MALLOC_ERROR, s);
		}
		ft_setenv(s, tmp);
		free_2d_array((void **)split_str);
		free(str);
		return (1);
	}
	return (0);
}

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
		free_and_exit(MALLOC_ERROR, s);
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
			free_and_exit(MALLOC_ERROR, s);
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
		free_and_exit(MALLOC_ERROR, s);
	}
	s->env[i] = tmp_str;
	i++;
	s->env[i] = NULL;
	free_2d_array((void **)tmp);
	return (0);
}

int	ft_print_export(char **s_envp, t_shell *s)
{
	char	**dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dup = dup_envp(s_envp, s);
	sort_var_list(dup);
	ft_print_export_lines(dup, i, j);
	free_2d_array((void **)dup);
	return (0);
}
