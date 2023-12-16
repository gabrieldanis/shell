/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/16 17:41:43 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*expand_envp_str(char *str)
{
	char	*expanded;
	char	**split_str;
	int	i;

	expanded = NULL;
	i = 0;
	if (!ft_strchr(str, '=')) 
		expanded = expand_var(str);
	else
	{
		split_str = ft_split(str, '=');
		expanded = ft_strjoin(expanded, split_str[i]);
		expanded = ft_strjoin(expanded, "=");
		i++;
		while (split_str[i])
			expanded = ft_strjoin(expanded, split_str[i++]);
	}
	return (expanded);
}

int	ft_export(char **envp, t_parsed *list, int env)
{
	static char	**s_envp;
	char		*expanded_str;

	if (!s_envp)
		s_envp = dup_envp(envp);
	if (env)
		return (ft_env(s_envp), 0);
	if (!list->next || list->next->type != 0)
		return (ft_print_export(s_envp), 0);
	list = list->next;
	while (list && list->type == 0)
	{
		expanded_str = expand_envp_str(list->str);
		ft_setenv(&s_envp, expanded_str);
		list = list->next;
	}
	return (0);
}

void	ft_setenv(char ***envp, char *str)
{
	char	**tmp;
	int	i;

	i = 0;
	tmp = *envp;
	while ((*envp)[i])
		i++;
	*envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "_=", 2))
	{
		(*envp)[i] = tmp[i]; 
		i++;
	}
	(*envp)[i] = str;
	i++;
	(*envp)[i] = tmp[i - 1];
	i++;
	(*envp)[i] = NULL;
	free(tmp);
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
