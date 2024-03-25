/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 10:23:46 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_signal(t_shell *s)
{
	struct sigaction	sig1;
	struct sigaction	sig2;

	sig1 = (struct sigaction){0};
	sig2 = (struct sigaction){0};
	sig1.sa_handler = &handle_sig1;
	sig2.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sig1, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
	if (sigaction(SIGQUIT, &sig2, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
}

void	child_signal(t_shell *s)
{
	struct sigaction	sig_child_1;
	struct sigaction	sig_child_2;

	sig_child_1 = (struct sigaction){0};
	sig_child_2 = (struct sigaction){0};
	sig_child_1.sa_handler = &handle_sig_child_1;
	sig_child_1.sa_flags = SA_RESTART;
	sig_child_2.sa_handler = &handle_sig_child_2;
	sig_child_2.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig_child_1, NULL) == -1)
		free_and_exit(SIG_ERROR, s, NULL, NULL);
	if (sigaction(SIGQUIT, &sig_child_2, NULL) == -1)
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
