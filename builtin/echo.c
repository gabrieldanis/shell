/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/01 19:18:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_echo(t_parsed *lst)
{
	int	nl;
	int	i;

	i = 1;
	nl = 1;
	if (lst->arglst[i] && !ft_strncmp(lst->arglst[i], "-n\0", 3))
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
}
