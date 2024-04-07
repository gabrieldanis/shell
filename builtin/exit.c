/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:23:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/07 20:25:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	mnc(const char *nptr)
{
	long long	number;
	int			minus;
	long long	max;

	max = 9223372036854775807;
	minus = 0;
	number = 0;
	if (*nptr == '-')
		minus++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (number - minus <= max / 10)
			number = number * 10;
		else
			return (1);
		if (number - minus <= max - (*nptr - '0'))
			number = number + (*nptr - '0');
		else
			return (1);
		nptr++;
	}
	return (0);
}

int	exit_wrong_argnum(t_shell *s, t_parsed *node)
{
	if (node)
	{
		s->rval = 1;
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
				|| lst->lst->next->str[0] == '\0' || mnc(lst->lst->next->str))
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
