/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/08 11:44:58 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	signal_handler(int num)
{
	if (num == 0)
	{
		signal(SIGINT, &handle_sig1);
		signal(SIGQUIT, SIG_IGN);
	}

	if (num == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}

	if (num == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	ft_signal(t_shell *s)
{
	struct sigaction	sig1;
	struct sigaction	sig2;

	memset(&sig1, 0, sizeof(sig1));
	memset(&sig2, 0, sizeof(sig2));
	s->sig1 = sig1;
	s->sig2 = sig2;
	s->sig1.sa_handler = &handle_sig1;
	s->sig2.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &(s->sig1), NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
	if (sigaction(SIGQUIT, &(s->sig2), NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
}

void	child_signal(t_shell *s)
{
	s->sig1.sa_handler = &handle_sig_child_1;
	s->sig1.sa_flags = SA_RESTART;
	s->sig2.sa_handler = &handle_sig_child_2;
	s->sig2.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s->sig1, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
	if (sigaction(SIGQUIT, &s->sig2, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
}

void	signal_while_child(t_shell *s)
{
	s->sig1.sa_handler = SIG_IGN;
	s->sig2.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &s->sig1, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
	if (sigaction(SIGQUIT, &s->sig2, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
}

void	ft_signal_heredoc(t_shell *s)
{
	struct sigaction	sig1_heredoc;

	sig1_heredoc = (struct sigaction){0};
	sig1_heredoc.sa_handler = &handle_sig1_heredoc;
	if (sigaction(SIGINT, &sig1_heredoc, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
}
