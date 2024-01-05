/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/05 16:56:57 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_exit(t_shell *s, t_parsed *lst)
{
	int	i;

	printf("exit\n");
	if(lst && lst->lst->next)
	{
		i = 0;
		while (lst->lst->next->str[i])
		{
			if (!ft_isdigit(lst->lst->next->str[i]))	
			{
				s->rval = 2;
				error_message(NUM_ERROR, "exit", NULL, s);
				free_and_exit(0, s);
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
	free_and_exit(0, s);
}
