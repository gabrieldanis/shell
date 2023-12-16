/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/16 15:49:58 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	alpha_smlr(char *i, char *j)
{
	while (*i == *j && *i != '=' && *j != '=')
	{
		i++;
		j++;
	}
	if (*j == '=' || *j < *i)
		return (1);
	else
		return (0);
}

void	sort_var_list(char **dup)
{
	char	*swap;
	int	i;
	int	j;	

	i = 0;
	while (dup[i] && dup[i + 1])
	{
		j = i + 1;
		while (dup[j])
		{
			if (alpha_smlr(dup[i], dup[j]))	
			{
				swap = dup[i];
				dup[i] = dup[j];
				dup[j] = swap;
			}
			j++;
		}
		i++;
	}
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
//	printf("new var in envp = %s\n", (*envp)[i]);
	i++;
	(*envp)[i] = tmp[i - 1];
	i++;
	(*envp)[i] = NULL;
	//free(tmp);
}

int	ft_export(char **envp, t_parsed *list)
{
	static char	**s_envp;

	if (!s_envp)
		s_envp = envp;
	if (!list->next || list->next->type != 0)
		return (ft_print_export(s_envp), 0);
	list = list->next;
	while (list && list->type == 0)
	{
		ft_setenv(&s_envp, list->str);
		list = list->next;
	}
	return (0);
}

int	ft_print_export(char **envp)
{
	char	**dup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (envp[j])
	{
		if (strncmp(envp[j], "_=", 2))
		{
			dup[i] = envp[j];
			i++;
			j++;
		}
		else
			j++;
	}
	dup[i] = NULL;
	sort_var_list(dup);
	i = 0;
	while (dup[i])
	{
		write(1, "declare -x ", 11);
		j = 0;
		while (dup[i][j] != '=' && dup[i][j])
		{
			write(1, &(dup[i][j]), 1);	
			j++;
		}
		if (dup[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while(dup[i][j])
			{
				write(1, &(dup[i][j]), 1);	
				j++;
			}
			write(1, "\"\n", 2);
		}
		i++;
	}
	free(dup);
	return (0);
}
