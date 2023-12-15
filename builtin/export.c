/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:28:20 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/15 12:02:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	alpha_smlr(char *i, char *j)
{
	// if j smaller than i return 1
	return (0);
}

void	sort_var_list(char **dup)
{
	char	*swap;
	int	i;
	int	j;	

	i = 0;
	while (dup[i + 1])
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

int	ft_export(char **envp)
{
	char	**dup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i - 1));
	i = 0;
	while (envp[j])
	{
		if (envp[j][0] != '_' && envp[j][1] != '=')
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
		printf("%s\n", dup[i]);
		i++;
	}
	free(dup);
	return (0);
}
