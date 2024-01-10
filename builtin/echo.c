/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/10 13:22:10 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_echo(t_parsed *lst)
{
	int	nl;
	int	i;

	i = 1;
	nl = 1;
	while (lst->arglst[i] && !ft_strncmp(lst->arglst[i], "-n\0", 3))
	{
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
