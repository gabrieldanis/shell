/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/20 14:29:22 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	error_message(int n, char *exe_name, char *str)
{
	printf("minishell: ");
	if (exe_name)
		printf("%s: ", exe_name);
	if (str)
		printf("`%s': ", str);
	if (n == 1)
		printf("malloc error\n");
	if (n == 2)
		printf("unclosed quotation mark\n");
	if (n == 3)
		printf("not a valid identifier\n");
	else
		printf("unknown error\n");
}
