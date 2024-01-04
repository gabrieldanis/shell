/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/04 10:40:45 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s)
{
	free_lsts(s);
	printf("minishell: ");
	if (exe_name)
		printf("%s: ", exe_name);
	if (str && n != 9)
		printf("`%s': ", str);
	if (n == 1)
		printf("malloc error\n");
	else if (n == 2)
		printf("unclosed quotation mark\n");
	else if (n == 3)
		printf("not a valid identifier\n");
	else if (n == 4)
		printf("error");
	else if (n == 5)
		printf("no such file or directory\n");
	else if (n == 6)
		printf("command not found\n");
	else if (n == 7)
		printf("execve error\n");
	else if (n == 8)
		printf("fork error\n");
	else if (n == 9)
	{
		printf("syntax error near unexpected token `%s'\n", str);
	}
	else if (n == ARGNUM_ERROR)
		printf("too many arguments\n");
	else
		printf("unknown error\n");
	return (n);
}
