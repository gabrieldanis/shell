/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:44:09 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_exit(t_shell *s, t_parsed *lst)
{
	int	i;

	ft_putstr_fd("exit\n", 2);
	if (lst && lst->lst->next)
	{
		i = 0;
		while (lst->lst->next->str[i])
		{
			if (!ft_isdigit(lst->lst->next->str[i]))
			{
				s->rval = 2;
				error_message(NUM_ERROR, "exit", lst->lst->next->str, s);
				free_and_exit(0, s, NULL, NULL);
			}
			i++;
		}
		if (lst->lst->next->next)
		{
			s->rval = 1;
			error_message(ARGNUM_ERROR, "exit", NULL, s);
			return ;
		}
		s->rval = ft_atoi(lst->lst->next->str);
	}
	free_and_exit(0, s, NULL, NULL);
}
