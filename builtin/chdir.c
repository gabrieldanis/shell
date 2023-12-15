/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:17:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/15 09:33:34 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_chdir(t_parsed *list)
{
	int	rvalue;

	rvalue = chdir(list->next->str);
	if (rvalue == -1)
		printf ("minishell: %s: %s: no such file or directory\n", list->str, list->next->str);
	return (rvalue);
}
