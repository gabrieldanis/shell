/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/08 13:22:01 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_exit(t_shell *s, t_parsed *lst)
{
	int	i;
	unsigned char	num;

	if (lst && lst->lst->next)
	{
		i = 0;
		if (lst->lst->next->str[0] == '+' || lst->lst->next->str[0] == '-')
			i++;
		while (lst->lst->next->str[i] || lst->lst->next->str[0] == '\0')
		{
			if (!ft_isdigit(lst->lst->next->str[i]) || lst->lst->next->str[0] == '\0')
			{
				free_s_str(s);
				errno = 2;
				free_and_exit(NUM_ERROR, s, "exit", lst->lst->next->str, errno);
			}
			i++;
		}
		if (lst->lst->next->next)
		{
			s->rval = 1;
			free_s_str(s);
			error_message(ARGNUM_ERROR, "exit", NULL, s, errno);
			return ;
		}
		num = ft_atoi(lst->lst->next->str);
		s->rval = num;
	}
	free_s_str(s);
	free_and_exit(0, s, NULL, NULL, errno);
}
