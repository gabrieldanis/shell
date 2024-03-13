/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/09 11:57:21 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s)
{

	//printf("err = %d, n = %d\n", err , n);
	if (n != ENV_ERROR)
		ft_putstr_fd("minishell: ", 2);
	if (exe_name)
	{
		ft_putstr_fd(exe_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n == NUM_ERROR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n != CMD_ERROR && n != UNEX_TOKEN && n!= ARGNUM_ERROR
			&& n!= NUM_ERROR && n != ENV_ERROR && n != IDENT_ERROR)
	{
		if (n == NOFILE_ERROR)
			s->rval = 127;
		else if (n == ISDIR_ERROR || n == PERM_ERROR)
			s->rval = 126;
		else if (n == NOINFILE_ERROR || n == OUTFILE_ERROR
				|| n == WRITE_ERROR || n == NOCDFILE_ERROR)
			s->rval = 1;
		else
			s->rval = errno;
		perror(str);
	}
	if (n == ENV_ERROR)
	{
		s->rval = 127;
		perror(str);
	}
	if (n == CMD_ERROR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		s->rval = 127;
		return(ft_putstr_fd("command not found\n", 2), 127);
	}
	else if (n == UNEX_TOKEN)
	{
		ft_putstr_fd("syntax error near unexpected token: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
		s->rval = 2;
	}
	else if (n == NUM_ERROR)
	{
		ft_putstr_fd("numeric argument required\n", 2);
		s->rval = 2;
	}
	else if (n == ARGNUM_ERROR)
		ft_putstr_fd("too many arguments\n", 2);
	else if (n == IDENT_ERROR)
	{
		if (errno == 2)
			ft_putstr_fd("invalid option\n", 2);
		else
			ft_putstr_fd("invalid idenftifier\n", 2);
		s->rval = errno;
	}
	return (s->rval);
}
