/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:29:39 by dberes            #+#    #+#             */
/*   Updated: 2024/03/20 10:22:27 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	pipe_syntax_check(t_shell *s, t_token *node)
{
	if (s->tlst->type == PIPE)
	{
		error_message(UNEX_TOKEN, NULL, "|", s);
		return (1);
	}
	if (node->type == PIPE)
	{
		if (node->next->type == PIPE || !node->next)
		{
			error_message(UNEX_TOKEN, NULL, "|", s);
			return (1);
		}
	}
	return (0);
}

int	syntax_check(t_shell *s)
{
	t_token	*node;

	node = s->tlst;
	while (node)
	{
		if (node->type == HEREDOC || node->type == RED_IN
			|| node->type == RED_OUT || node->type == RED_APP)
		{
			if (check_eof(s, node))
				return (1);
		}
		if (check_pipe(s, node))
			return (1);
		node = node->next;
	}
	return (0);
}

int	check_eof(t_shell *s, t_token *node)
{
	if (!node->next)
	{
		free_s_str(s);
		error_message(UNEX_TOKEN, NULL, "newline", s);
		return (1);
	}
	if (node->next->type)
	{
		free_s_str(s);
		error_message(UNEX_TOKEN, NULL, node->next->str, s);
		return (1);
	}
	return (0);
}

int	check_pipe(t_shell *s, t_token *node)
{
	if (s->tlst->type == PIPE)
	{
		free_s_str(s);
		error_message(UNEX_TOKEN, NULL, "|", s);
		return (1);
	}
	if (node->type == PIPE)
	{
		if (node->next->type == PIPE || !node->next)
		{
			free_s_str(s);
			error_message(UNEX_TOKEN, NULL, "|", s);
			return (1);
		}
	}
	return (0);
}
