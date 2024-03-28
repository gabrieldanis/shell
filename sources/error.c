/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/28 07:11:20 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	perror_message(t_shell *s, char *str, int n)
{
	if (n != CMD_ERROR && n != UNEX_TOKEN && n != ARGNUM_ERROR
		&& n != NUM_ERROR && n != ENV_ERROR && n != IDENT_ERROR
		&& n != MALLOC_ERROR && n != NOHOME_ERROR && n != HEREDOC_EOF_ERROR
		&& n != QUOTE_ERROR)
	{
		if (n == NOFILE_ERROR && errno != 13)
			s->rval = 127;
		else if (n == ISDIR_ERROR
			|| (n == NOFILE_ERROR && errno == 13))
			s->rval = 126;
		else if (n == NOINFILE_ERROR || n == OUTFILE_ERROR
			|| n == WRITE_ERROR || n == NOCDFILE_ERROR || n == PERM_ERROR)
		{
			s->error = 1;
			if (n != WRITE_ERROR)
				perror(str);
			return (s->rval = 1, 1);
		}
		else
			s->rval = errno;
		perror(str);
		return (1);
	}
	return (0);
}

void	syntax_errors(t_shell *s, char *str, int n, char *exe_name)
{
	if (n == UNEX_TOKEN)
	{
		ft_putstr_fd("syntax error near unexpected token: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
		s->rval = 2;
	}
	if (n == NUM_ERROR)
	{
		if (!ft_strncmp(exe_name, "exit", 5))
			printf("exit\n");
		ft_putstr_fd("numeric argument required\n", 2);
		s->rval = 2;
	}
	if (n == ARGNUM_ERROR)
		ft_putstr_fd("too many arguments\n", 2);
	if (n == IDENT_ERROR)
	{
		if (errno == 2)
			ft_putstr_fd("invalid option\n", 2);
		else
			ft_putstr_fd("invalid idenftifier\n", 2);
		s->rval = errno;
	}
}

void	builtin_error(t_shell *s, char *str, int n)
{
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
		ft_putstr_fd("command not found\n", 2);
	}
}

void	custom_message(t_shell *s, char *str, int n, char *exe_name)
{
	if (n == NUM_ERROR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n == HEREDOC_EOF_ERROR)
	{
		ft_putstr_fd
			("warning: here-doc delimited by EOF instead of delimiter\n", 2);
		s->rval = 0;
	}
	if (n == MALLOC_ERROR)
	{
		ft_putstr_fd("malloc error\n", 2);
		if (s)
			s->rval = 1;
		else
			exit (1);
	}
	custom_message_quote_error(s, n);
	builtin_error(s, str, n);
	syntax_errors(s, str, n, exe_name);
}

int	error_message(int n, char *exe_name, char *str, t_shell *s)
{
	s->error = 1;
	if (n != ENV_ERROR)
		ft_putstr_fd("minishell: ", 2);
	if (exe_name)
	{
		ft_putstr_fd(exe_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (perror_message(s, str, n))
		return (s->rval);
	else
		custom_message(s, str, n, exe_name);
	return (s->rval);
}
