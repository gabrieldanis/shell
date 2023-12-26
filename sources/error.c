/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/26 12:00:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str)
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
	if (n == 4)
		printf("error");
	if (n == 5)
		printf("no such file or directory\n");
	if (n == 6)
		printf("command not found\n");
	if (n == 7)
		printf("execve error\n");
	else
		printf("unknown error\n");
	return (n);
}
