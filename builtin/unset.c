/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:29:32 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 22:28:53 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_unset(t_shell *s)
{
	t_parsed	*start;
	char		**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	start = s->lst;
	while (s->env[i])
	{
		i++;
	}
	s->lst = s->lst->next;
	while (s->lst)
	{

		if (!is_varname(s->lst->fstr))
		{
			error_message(IDENT_ERROR, "unset", s->lst->fstr);
		}
		else
		{
			tmp = (char **)malloc(sizeof(char *) * i);
			if (!tmp)
				free_and_exit(MALLOC_ERROR, s);
			i = 0;
			while (s->env[i + j])
			{
				if (!ft_strncmp(s->lst->fstr, s->env[i + j], ft_strlen(s->lst->fstr))
					&& (s->env[i + j][ft_strlen(s->lst->fstr)] == '='
						|| s->env[i + j][ft_strlen(s->lst->fstr)] == '\0'))
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
		s->lst = s->lst->next;
	}
	s->lst = start;
	return (0);
}
