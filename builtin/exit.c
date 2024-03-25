/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 13:47:48 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	exit_wrong_argnum(t_shell *s, t_parsed *node)
{
	if (node)
	{
		s->rval = 1;
		free_s_str(s);
		error_message(ARGNUM_ERROR, "exit", NULL, s);
		return (1);
	}
	return (0);
}

void	ft_exit(t_shell *s, t_parsed *lst)
{
	unsigned char	num;
	int				i;

	if (lst && lst->lst->next)
	{
		i = 0;
		if (lst->lst->next->str[0] == '+' || lst->lst->next->str[0] == '-')
			i++;
		while (lst->lst->next->str[i] || lst->lst->next->str[0] == '\0')
		{
			if (!ft_isdigit(lst->lst->next->str[i++])
				|| lst->lst->next->str[0] == '\0')
			{
				free_s_str(s);
				errno = 2;
				free_and_exit(NUM_ERROR, s, "exit", lst->lst->next->str);
			}
		}
		if (exit_wrong_argnum(s, lst->lst->next->next))
			return ;
		num = ft_atoi(lst->lst->next->str);
		s->rval = num;
	}
	printf("exit\n");
	free_and_exit(0, s, NULL, NULL);
}
