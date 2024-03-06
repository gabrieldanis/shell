/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/05 12:08:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	nl_flagchecker(char *str)
{
	int	i;

	if (str[0] != '-')
		return (1);
	i = 1;
	if (str[i] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')	
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_parsed *lst)
{
	int	nl;
	int	i;

	i = 1;
	nl = 1;
	while (lst->arglst[i])
	{
		if (nl_flagchecker(lst->arglst[i]))
			break ;
		nl = 0;
		i++;
	}
	while (lst->arglst[i])
	{
		printf("%s", lst->arglst[i]);
		i++;
		if (lst->arglst[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}
