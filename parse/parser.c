/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 08:44:00 by gdanis   filename         #+#    #+#             */
/*   Updated: 2024/04/05 18:07:55 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parse_isfile(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	if (subnode->type == RED_IN && subnode->next && !subnode->next->type)
	{
		subnode->next->type = INFILE;
		node->infile = subnode->next->str;
	}
	if (subnode->type == HEREDOC)
		node->infile = subnode->filename;
	if ((subnode->type == RED_OUT || subnode->type == RED_APP) && subnode->next
		&& !subnode->next->type)
	{
		subnode->next->type = OUTFILE;
		appln_chararr(node, subnode->next->str, s);
		if (subnode->type == RED_OUT)
			node->append = 0;
		else
			node->append = 1;
	}
	return (1);
}

int	parse_cmdargs(t_parsed *node, t_parsed *subnode, t_shell *s)
{
	static int	cmd;

	(void)s;
	(void)node;
	if (!subnode->type && !cmd)
	{
		subnode->type = CMD;
		cmd = 1;
	}
	if (!subnode->type && cmd)
		subnode->type = ARG;
	if (!subnode->next)
		cmd = 0;
	return (1);
}
