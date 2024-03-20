/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:27:49 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 10:28:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	node_dup(t_parsed *node, t_token *t_node, char *s2, t_shell *s)
{
	node->str = ft_strdup(s2);
	if (!node->str)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	node->type = t_node->type;
}
