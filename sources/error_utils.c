/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:41:26 by dberes            #+#    #+#             */
/*   Updated: 2024/04/08 12:48:49 by gdanis           ###   ########.fr       */
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

void	ident_error_check(t_shell *s, char *str)
{
	if (errno == 2)
		ft_putstr_fd("invalid option\n", 2);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	s->rval = errno;
}
