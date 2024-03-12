/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/12 13:33:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s, int err)
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
			&& n != NUM_ERROR && n != ENV_ERROR && n != IDENT_ERROR 
			&& n != MALLOC_ERROR && n != NOHOME_ERROR && n != HEREDOC_EOF_ERROR)
	{
		if (n == NOFILE_ERROR)
			s->rval = 127;
		else if (n == ISDIR_ERROR || n == PERM_ERROR)
			s->rval = 126;
		else if (n == NOINFILE_ERROR || n == OUTFILE_ERROR
				|| n == WRITE_ERROR || n == NOCDFILE_ERROR)
			s->rval = 1;
		else
			s->rval = err;
		perror(str);
	}
	if (n == HEREDOC_EOF_ERROR)
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file instead of delimiter\n", 2);
		s->rval = 0;
	}
	if (n == MALLOC_ERROR)
	{
		ft_putstr_fd("malloc error\n", 2);
		s->rval = 1;
	}
	if (n == NOHOME_ERROR)
	{
		ft_putstr_fd("HOME not set\n", 2);
		s->rval = 1;
	}
	if (n == ENV_ERROR)
	{
		s->rval = 127;
		perror(str);
	}
	if (n == CMD_ERROR)
	{
		if (str)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
		}
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
		if (err == 2)
			ft_putstr_fd("invalid option\n", 2);
		else
			ft_putstr_fd("invalid idenftifier\n", 2);
		s->rval = err;
	}
	return (s->rval);
}
