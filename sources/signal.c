/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/12 18:36:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_signal(t_shell *s)
{
	signal(SIGINT, handle_sig1);
	signal(SIGQUIT, SIG_IGN);
	(void)s;
}

void	child_signal(void)
{
	signal(SIGINT, handle_sig_child_1);
	signal(SIGQUIT, handle_sig_child_2);
}

void	ft_signal_heredoc(t_shell *s)
{
	signal(SIGINT, handle_sig1_heredoc);
	(void)s;
}

void	handle_sig1(int signal_num)
{
	(void)signal_num;
	write(1, "\n", 1); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
   	rl_replace_line("", 0); // Clear the previous text
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
	write(1, "\n", 1); // Move to a new line
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
	rl_replace_line("", 0); // Clear the previous text
    rl_on_new_line(); // Regenerate the prompt on a newline
	g_var = 130;
}
