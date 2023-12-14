/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:34:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/14 15:43:05 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_exit(t_parsed *list)
{
	int	err_code;

	err_code = 0;
	/*
	 * free all memory
	 */
	(void)list;
	printf("exit\n");
	exit(err_code);
}
