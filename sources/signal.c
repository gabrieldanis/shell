/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/16 16:03:49 by gdanis           ###   ########.fr       */
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
