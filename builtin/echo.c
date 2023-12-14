/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:19:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/14 15:27:33 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_echo(t_parsed *list)
{
	while (list)
	{
		if (list->expand)
			printf("%s", list->expand);
		else
			printf("%s", list->str);
		list = list->next;
		if (list)
			printf(" ");
	}
	printf("\n");
}


