/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/12 10:39:05 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s)
{
	ft_putstr_fd("minishell: ", 2);
	if (exe_name)
	{
		ft_putstr_fd(exe_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str && n != UNEX_TOKEN)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n == MALLOC_ERROR)
		ft_putstr_fd("malloc error\n", 2);
	else if (n == QUOTE_ERROR)
		ft_putstr_fd("unclosed quotation mark\n", 2);
	else if (n == IDENT_ERROR)
		ft_putstr_fd("not a valid identifier\n", 2);
	else if (n == GEN_ERROR)
		ft_putstr_fd("error", 2);
	else if (n == NOFILE_ERROR)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (n == CMD_ERROR)
		ft_putstr_fd("command not found\n", 2);
	else if (n == EXECVE_ERROR)
		ft_putstr_fd("execve error\n", 2);
	else if (n == FORK_ERROR)
		ft_putstr_fd("fork error\n", 2);
	else if (n == UNEX_TOKEN)
	{
		ft_putstr_fd("syntax error near unexpected token: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (n == ARGNUM_ERROR)
		ft_putstr_fd("too many arguments\n", 2);
	else if (n == NUM_ERROR)
		ft_putstr_fd("numeric argument required\n", 2);
	else
		ft_putstr_fd("unknown error\n", 2);
	free_lsts(s);
	return (n);
}
