/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/04 11:11:17 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_export(t_shell *s, t_parsed *lst, int env)
{
	int	i;

	i = 0;
	if (env)
		return (ft_env(s), 0);
	if (!lst->arglst[1])
		return (ft_print_export(s->env), 0);
	i++;
	while (lst->arglst[i])
	{
		ft_setenv(s, lst->arglst[i]);
		i++;
	}
	return (0);
}

int	update_existing_var(t_shell *s, char *str)
{
	int	i;
	int	len;
	char	*tmp;

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
			s->env[i] = ft_strdup(str);
			if (!s->env[i])
				free_and_exit(MALLOC_ERROR, s);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	append_var(t_shell *s, char *str)
{
	int	len;
	int	i;
	char	*tmp;
	char	**split_str;

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
				tmp = s->env[i];
				s->env[i] = ft_strjoin(s->env[i], str + len + 2);
				if (!s->env[i])
					free_and_exit(MALLOC_ERROR, s);
				free(tmp);
				return (1);
			}
			if (!ft_strncmp(s->env[i], str, len)
				&& s->env[i][len] == '\0')
			{
				tmp = s->env[i];
				s->env[i] = ft_strjoin(s->env[i], "=");
				if (!s->env[i])
					free_and_exit(MALLOC_ERROR, s);
				free(tmp);
				tmp = s->env[i];
				s->env[i] = ft_strjoin(s->env[i], str + len + 2);
				if (!s->env[i])
					free_and_exit(MALLOC_ERROR, s);
				free(tmp);
				return (1);
			}
			i++;
		}
		split_str = ft_split(str, '+');
		if (!split_str)
			free_and_exit(MALLOC_ERROR, s);
		tmp = ft_strjoin(split_str[0], split_str[1]);
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s);
		ft_setenv(s, tmp);
		free(tmp);
		free_2d_array((void **)split_str);
		return (1);
	}
	return (0);
}

int	ft_setenv(t_shell *s, char *str)
{
	char	**tmp;
	int	i;

	if (!is_varname(str))
		return (error_message(IDENT_ERROR, "export", str, s), 1);
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
		free_and_exit(MALLOC_ERROR, s);
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "_=", 2))
	{
		s->env[i] = tmp[i]; 
		i++;
	}
	s->env[i] = ft_strdup(str);
	if (!s->env)
		free_and_exit(MALLOC_ERROR, s);
	i++;
	s->env[i] = tmp[i - 1];
	i++;
	s->env[i] = NULL;
	free(tmp);
	return (0);
}

int	ft_print_export(char **s_envp)
{
	char	**dup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	dup = dup_envp(s_envp);
	sort_var_list(dup);
	ft_print_export_lines(dup, i, j);
	free_2d_array((void **)dup);
	return (0);
}
