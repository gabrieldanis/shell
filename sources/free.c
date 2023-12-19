/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:49 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 13:21:46 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

void	free_and_exit(int n)
{
	if (n == 1)
		printf("malloc error\n");
	if (n == 2)
		printf("error: unclosed quotation mark\n");
	else
		printf("need to free everything here\n");
	exit (1);
}
