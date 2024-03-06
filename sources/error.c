/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:07:21 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/04 12:45:13 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	error_message(int n, char *exe_name, char *str, t_shell *s, int err)
{

	(void) n;
	ft_putstr_fd("minishell: ", 2);
	if (exe_name)
	{
		ft_putstr_fd(exe_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n != CMD_ERROR && n != UNEX_TOKEN && n!= ARGNUM_ERROR)
	{
		if (err == 21 || n == NOFILE_ERROR)
			s->rval = 1;
		else
			s->rval = err;
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
	else if (n == ARGNUM_ERROR)
		ft_putstr_fd("too many arguments\n", 2);
	/*if (str && n != UNEX_TOKEN && n != HEREDOC_EOF_ERROR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (n == WRITE_ERROR || n == READ_ERROR || n == DUP_ERROR || n == PERM_ERROR)
		fd_closer(s);
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
	else if (n == EXECVE_ERROR)
		return (ft_putstr_fd("Command not found\n", 2), 127);
	else if (n == FORK_ERROR)
		ft_putstr_fd("fork error\n", 2);
	
	
	else if (n == NUM_ERROR)
		ft_putstr_fd("numeric argument required\n", 2);
	//else if (n == WRITE_ERROR)
	//	ft_putstr_fd("write to file failed\n", 2);
	else if (n == READ_ERROR)
		ft_putstr_fd("read from file failed\n", 2);
	else if (n == DUP_ERROR)
		ft_putstr_fd("dup2 error\n", 2);
	else if (n == PERM_ERROR)
		return (ft_putstr_fd("Permission denied\n", 2), 126);
	else if (n == RL_ERROR)
		ft_putstr_fd("Readline error\n", 2);
	else if (n == OPEN_ERROR)
		ft_putstr_fd("failed to open file\n", 2);
	else if (n == UNLINK_ERROR)
		ft_putstr_fd("failed to unlink file\n", 2);
	else if (n == HEREDOC_EOF_ERROR)
	{
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("')\n", 2);
	}
	else
		ft_putstr_fd("unknown error\n", 2);*/
	//free_lsts(s);
	return (s->rval);
}
