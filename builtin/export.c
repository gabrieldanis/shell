/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/17 10:32:06 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*expand_envp_str(char *str)
{
	char	*expanded;
	char	**split_str;

	expanded = NULL;
	if (!ft_strchr(str, '=')) 
		expanded = expand_var(str);
	else
	{
		split_str = ft_split(str, '=');
		if (!split_str)
			return (NULL);
		expanded = ft_strjoin(expanded, expand_var(split_str[0]));
		free_2d_array((void **)split_str);
		expanded = ft_strjoin(expanded, "=");
		if (*(ft_strchr(str, '=') + 1))
			expanded = ft_strjoin(expanded, expand_var(ft_strchr(str, '=') + 1));
	}
	return (expanded);
}

int	ft_export(char **envp, t_parsed *list, int env)
{
	static char	**s_envp;
	int	i;

	if (!s_envp)
		s_envp = dup_envp(envp);
	if (env)
		return (ft_env(s_envp), 0);
	////////////////once parsing works the 0 here must be replaced
	if (!list->next)// || list->next->type != 0)
		return (ft_print_export(s_envp), 0);
	list = list->next;
	////////////////once parsing works the 0 here must be replaced
	while (list)// && list->type == 0)
	{
		if (list->type == 9 || list->type == 10)
			list->expand = expand_envp_str(list->expand);
		else
		{
			if (list->expand)
				free(list->expand);
			list->expand = expand_envp_str(list->str);
		}
		ft_setenv(&s_envp, list->expand);
		list = list->next;
		i = 0;
		while (s_envp[i])
			printf("%s\n", s_envp[i++]);
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
