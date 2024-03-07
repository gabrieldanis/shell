/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:39 by dberes            #+#    #+#             */
/*   Updated: 2024/03/07 12:36:07 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	syntax_check(t_shell *s);
{
	t_token *node;

	node = s->tlst;
	while(node)
	{
		if (node->type == HEREDOC)
		{
			if (!node->next)
			{
				errno = 2;
				error_message(EXPTOK_ERROR, NULL, "newline", s, errno);
				return ;
			}
		}
		node = node->next;	
	}
}