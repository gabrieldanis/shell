/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:41:26 by dberes            #+#    #+#             */
/*   Updated: 2024/03/21 14:41:29 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	custom_message_quote_error(t_shell *s, int n)
{
	if (n == QUOTE_ERROR)
	{
		ft_putstr_fd
			("error: unclosed quote\n", 2);
		s->rval = 1;
	}
}
