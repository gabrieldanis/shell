/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:39 by dberes            #+#    #+#             */
/*   Updated: 2024/03/07 12:46:37 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int	syntax_check(t_shell *s)
{
	t_token *node;

	node = s->tlst;
	while(node)
	{
		if (node->type == HEREDOC)
		{
			if (!node->next)
			{
				error_message(UNEX_TOKEN, NULL, "newline", s, errno);
				return (1);
			}
		}
		if (node->type == HEREDOC)
		{
			if (node->next->type)
			{
				error_message(UNEX_TOKEN, NULL, node->next->str, s, errno);
				return (1);
			}
		}
		node = node->next;	
	}
	return (0);
}