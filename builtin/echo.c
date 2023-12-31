/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/30 22:22:10 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_echo(t_token *list)
{
	int	nl;

	nl = 1;
	if (list && !ft_strncmp(list->str, "-n\0", 3))
	{
		nl = 0;
		list->ex = list->next;
	}
	while (list)
	{
		printf("%s", list->str);
		list = list->next;
		if (list)
			printf(" ");
	}
	if (nl)
		printf("\n");
}
