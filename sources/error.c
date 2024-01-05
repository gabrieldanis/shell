/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/05 14:31:25 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s)
{
	free_lsts(s);
	printf("minishell: ");
	if (exe_name)
		printf("%s: ", exe_name);
	if (str && n != UNEX_TOKEN)
		printf("`%s': ", str);
	if (n == MALLOC_ERROR)
		printf("malloc error\n");
	else if (n == QUOTE_ERROR)
		printf("unclosed quotation mark\n");
	else if (n == IDENT_ERROR)
		printf("not a valid identifier\n");
	else if (n == GEN_ERROR)
		printf("error");
	else if (n == NOFILE_ERROR)
		printf("no such file or directory\n");
	else if (n == CMD_ERROR)
		printf("command not found\n");
	else if (n == EXECVE_ERROR)
		printf("execve error\n");
	else if (n == FORK_ERROR)
		printf("fork error\n");
	else if (n == UNEX_TOKEN)
	{
		printf("syntax error near unexpected token `%s'\n", str);
	}
	else if (n == ARGNUM_ERROR)
		printf("too many arguments\n");
	else if (n == NUM_ERROR)
		printf("numeric argument required\n");
	else
		printf("unknown error\n");
	return (n);
}
