/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:29:32 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/21 10:30:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_unset(char ***envp, t_parsed *list)
{
	char	*arg;
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		i++;
	}
	list = list->next;
	while (list)
	{
		if (list->expand)
			arg = list->expand;
		else
			arg = list->str;
		if (!is_varname(arg))
		{
			error_message(IDENT_ERROR, "unset", arg);
		}
		else
		{
			tmp = (char **)malloc(sizeof(char *) * i);
			i = 0;
			while ((*envp)[i + j])
			{
				if (!ft_strncmp(arg, (*envp)[i + j], ft_strlen(arg))
					&& ((*envp)[i + j][ft_strlen(arg)] == '=' || (*envp)[i + j][ft_strlen(arg)] == '\0'))
				{
					free((*envp)[i]);
					j++;
				}
				if ((*envp)[i + j])
				{
					tmp[i] = (*envp)[i + j];
					i++;
				}
			}
			tmp[i] = NULL;
			free(*envp);
			*envp = tmp;
		}
		list = list->next;
	}
	return (0);
}
