/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/08 09:38:36 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	export_without_argument(t_shell *s, t_parsed *lst, int env)
{
	if (env)
		return (ft_env(s, lst), 1);
	if (!lst->arglst[1])
		return (ft_print_export(s->env, s), 1);
	return (0);
}

int	ft_export(t_shell *s, t_parsed *lst, int env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (export_without_argument(s, lst, env))
		return (0);
	i++;
	while (lst->arglst[i])
	{
		if (!is_varname(lst->arglst[i]))
		{
			if (lst->arglst[i][0] == '-')
				errno = 2;
			else
				errno = 1;
			error_message(IDENT_ERROR, "export", lst->arglst[i], s);
		}
		else
		{
			tmp = ft_strdup(lst->arglst[i]);
			if (!tmp)
				free_and_exit(MALLOC_ERROR, s, NULL, NULL);
			ft_setenv(s, tmp);
		}
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
				return (free(str), 1);
			tmp = s->env[i];
			s->env[i] = str;
			free(tmp);
			return (1);
		}
		i++;
	}
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
