/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:29:32 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/01 23:04:52 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	isenvar(char *env, char *varname)
{
	if (!ft_strncmp(varname, env, ft_strlen(varname))
		&& (env[ft_strlen(varname)] == '='
			|| env[ft_strlen(varname)] == '\0'))
		return (1);
	return (0);
}

int	ft_unset(t_shell *s, t_parsed *lst)
{
	char		**tmp;
	int		i;
	int		j;
	int		k;

	k = 1;
	if (!lst->arglst[1])
		return (0);
	while (lst->arglst[k])
	{
		i = 0;
		j = 0;
		while (s->env[i])
		{
			if (isenvar(s->env[i], lst->arglst[k]))
				j = 1;
			i++;
		}
		if (j)
		{
			tmp = (char **)malloc(sizeof(char *) * i);
			if (!tmp)
				free_and_exit(MALLOC_ERROR, s);
			i = 0;
			j = 0;
			while (s->env[i + j])
			{
				if (isenvar(s->env[i + j], lst->arglst[k]))
				{
					free(s->env[i]);
					j++;
				}
				if (s->env[i + j])
				{
					tmp[i] = s->env[i + j];
					i++;
				}
			}
			tmp[i] = NULL;
			free(s->env);
			s->env = tmp;
		}
		k++;
	}
	return (0);
}
