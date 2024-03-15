/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/15 16:56:25 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	create_space_token(t_shell *s, int *i, char *var, t_token *node)
{
	if (var[*i] == ' ' || var[*i] == '\t')
	{
		while (var[*i] == ' ' || var[*i] == '\t')
			(*i)++;
		if (last_token(node->ex)->str)
			token_addlstlast(&node->ex, s);
	}
}

void	expand_splittable_vars(t_shell *s, t_token *node, t_token *sp_node)
{
	int		i;

	if (sp_node->str[1] == '?' && sp_node->str[2] == '\0')
		s->var = token_vardup(NULL, s, EXIT_VALUE);
	else
	{
		if (ft_getenv(sp_node->str + 1, s))
			s->var = token_vardup(ft_getenv(sp_node->str + 1, s), s, 0);
		else
			s->var = NULL;
	}
	i = 0;
	while (s->var && s->var[i])
	{
		while (s->var[i] && s->var[i] != ' ' && s->var[i] != '\t')
			ft_charjoin(&last_token(node->ex)->str, s->var[i++], s);
		create_space_token(s, &i, s->var, node);
	}
	if (s->var)
	{
		free(s->var);
		s->var = NULL;
	}
}

void	expand_nonsplittable_vars(t_shell *s, t_token *node, t_token *sp_node)
{
	char	*var;

	var = NULL;
	if (sp_node->expand)
	{
		if (sp_node->str[1] == '?' && sp_node->str[2] == '\0')
			var = token_vardup(NULL, s, EXIT_VALUE);
		else
		{
			if (ft_getenv(sp_node->str + 1, s))
				var = token_vardup(ft_getenv(sp_node->str + 1, s), s, 0);
		}
	}
	else
		var = token_vardup(sp_node->str, s, 0);
	token_strjoin(&(last_token(node->ex)->str), &var, s);
	if (var)
		free (var);
}

void	expand_token(t_shell *s)
{
	t_token	*node;
	t_token	*sp_node;

	node = s->tlst;
	while (node)
	{
		token_addlstlast(&node->ex, s);
		sp_node = node->sp;
		while (sp_node)
		{
			if (ft_strchr(sp_node->str, '$') && ft_strlen(sp_node->str)
				!= 1 && sp_node->split)
				expand_splittable_vars(s, node, sp_node);
			else if (ft_strchr(sp_node->str, '$') && (ft_strlen(
						sp_node->str) != 1 || (ft_strlen(sp_node->str)
						== 1 && !sp_node->expand)))
				expand_nonsplittable_vars(s, node, sp_node);
			else if (!(ft_strchr(sp_node->str, '$')
					&& ft_strlen(sp_node->str) == 1))
				token_strjoin(&(last_token(node->ex)->str),
					&(sp_node->str), s);
			sp_node = sp_node->next;
		}
		node = node->next;
	}
}
