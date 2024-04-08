/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:10:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/08 12:32:14 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	signal_handler(int num)
{
	if (num == SIG_RL)
	{
		signal(SIGINT, &handle_sig1);
		signal(SIGQUIT, SIG_IGN);
	}
	if (num == SIG_MAIN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (num == SIG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (num == SIG_HEREDOC)
	{
		signal(SIGINT, &handle_sig1_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
