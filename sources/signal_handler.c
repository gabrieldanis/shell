/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:37 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/16 16:04:04 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	handle_sig1(int signal_num)
{
	(void)signal_num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
}

void	handle_sig2(int signal_num)
{
	(void)signal_num;
}

void	handle_sig_child_1(int signal_num)
{
	(void)signal_num;
	write(1, "\n", 1);
}

void	handle_sig_child_2(int signal_num)
{
	write(1, "Quit\n", 5);
	(void)signal_num;
}

void	handle_sig1_heredoc(int signal_num)
{
	(void)signal_num;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_var = 130;
}
