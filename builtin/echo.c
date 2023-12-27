/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 22:34:31 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_echo(t_parsed *list)
{
	int	nl;

	nl = 1;
	if (list && !ft_strncmp(list->fstr, "-n\0", 3))
	{
		nl = 0;
		list = list->next;
	}
	while (list)
	{
		printf("%s", list->fstr);
		list = list->next;
		if (list)
			printf(" ");
	}
	if (nl)
		printf("\n");
}
