/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/20 22:36:55 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_export(char ***envp, t_parsed *list, int env)
{
	char	*str;

	if (env)
		return (ft_env(*envp), 0);
	////////////////once parsing works the 0 here must be replaced
	if (!list->next)// || list->next->type != 0)
		return (ft_print_export(*envp), 0);
	list = list->next;
	////////////////once parsing works the 0 here must be replaced
	while (list)// && list->type == 0)
	{
		if (list->expand)
			str = list->expand;
		else
			str = list->str;
		ft_setenv(envp, str);
		list = list->next;
	}
	return (0);
}

int	update_existing_var(char **envp, char *str)
{
	int	i;
	int	len;
	char	*tmp;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len)
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
		{
			if (str[len] == '\0')
				return (1);
			tmp = envp[i];
			envp[i] = ft_strdup(str);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	append_var(char ***envp, char *str)
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
		while ((*envp)[i])
		{
			if (!ft_strncmp((*envp)[i], str, len)
				&& (*envp)[i][len] == '=')
			{
				tmp = (*envp)[i];
				(*envp)[i] = ft_strjoin((*envp)[i], str + len + 2);
				free(tmp);
				return (1);
			}
			if (!ft_strncmp((*envp)[i], str, len)
				&& (*envp)[i][len] == '\0')
			{
				tmp = (*envp)[i];
				(*envp)[i] = ft_strjoin((*envp)[i], "=");
				free(tmp);
				tmp = (*envp)[i];
				(*envp)[i] = ft_strjoin((*envp)[i], str + len + 2);
				free(tmp);
				return (1);
			}
			i++;
		}
		split_str = ft_split(str, '+');
		tmp = ft_strjoin(split_str[0], split_str[1]);
		ft_setenv(envp, tmp);
		free(tmp);
		free_2d_array((void **)split_str);
		return (1);
	}
	return (0);
}

int	ft_setenv(char ***envp, char *str)
{
	char	**tmp;
	int	i;

	if (!is_varname(str))
		return (error_message(IDENT_ERROR, "export", str), 1);
	if (update_existing_var(*envp, str))
		return (0);
	if (append_var(envp, str))
		return (0);
	i = 0;
	tmp = *envp;
	while ((*envp)[i])
		i++;
	*envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!(*envp))
		free_and_exit(MALLOC_ERROR);
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "_=", 2))
	{
		(*envp)[i] = tmp[i]; 
		i++;
	}
	(*envp)[i] = ft_strdup(str);
	i++;
	(*envp)[i] = tmp[i - 1];
	i++;
	(*envp)[i] = NULL;
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
	free(dup);
	return (0);
}
