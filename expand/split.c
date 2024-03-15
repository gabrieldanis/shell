/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:00:53 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/14 20:12:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	create_nonvar_token(t_shell *s, int *i, int *flag, t_token *node)
{
	static int		oldflag;

	if (!node->sp || (node->sp && last_token(node->sp)->str))
		token_addlstlast(&(node->sp), s);
	while (node->str[*i] && node->str[*i] != '$')
	{
		setqflag(flag, node->str[*i]);
		if (oldflag == *flag)
			ft_charjoin(&(last_token(node->sp)->str), node->str[*i], s);
		oldflag = *flag;
		(*i)++;
	}
	if (!last_token(node->sp)->str)
	{
		last_token(node->sp)->str = ft_strdup("");
		if (!last_token(node->sp)->str)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
}

void	check_nonvarname_char(int *i, int *non_varname_char, t_token *node)
{
	if (!check_is_var(node->str[*i]) && node->str[*i] != '?'
			&& node->str[*i] != '\0' && node->str[*i] != '"'
			&& node->str[*i] != 39 && node->str[*i] != ' '
			&& node->str[*i] != '=')
	{
		*non_varname_char = 1;
		last_token(node->sp)->expand = 0;
		last_token(node->sp)->split = 0;
	}
}

void	create_var_token(t_shell *s, int *i, int flag, t_token *node)
{
	int	non_varname_char;

	non_varname_char = 0;
	if (!node->sp || (node->sp && last_token(node->sp)->str))
		token_addlstlast(&node->sp, s);
	ft_charjoin(&(last_token(node->sp)->str), node->str[*i], s);
	(*i)++;
	if (!flag && node->type != HEREDOC_DEL)
		last_token(node->sp)->split = 1;
	if ((flag == 2 || flag == 0) && node->type != HEREDOC_DEL
		&& (check_is_var(node->str[*i]) || node->str[*i] == '?'))
		last_token(node->sp)->expand = 1;
	if (flag == 0 && !check_is_var(node->str[*i]) && node->str[*i] != '\0')
		last_token(node->sp)->expand = 1;
	check_nonvarname_char(i, &non_varname_char, node);
	while (check_is_var(node->str[*i]) || (node->str[*i] == '?'
			&& node->str[(*i) - 1] == '$') || non_varname_char)
	{
		ft_charjoin(&(last_token(node->sp)->str), node->str[*i], s);
		(*i)++;
		if ((node->str[(*i) - 1] == '?' && node->str[(*i) - 2] == '$') ||
		(non_varname_char && (!node->str[*i] || is_delimiter(*i) || node->str[*i] == '$')))
			break ;
		if ((node->str[*i] == '"' && flag == 2) || (node->str[*i] == 39 && flag == 1) ||
				(flag == 0 && (node->str[*i] == '"' || node->str[*i] == 39)))
			break;
	}
}

void	split_token(t_shell *s)
{
	t_token	*node;
	int		flag;
	int		i;

	flag = 0;
	node = s->tlst;
	while (node)
	{
		if (node->type == HEREDOC && node->next)
		{
			node->next->type = HEREDOC_DEL;
			if (ft_strchr(node->next->str, '\'') ||
				ft_strchr(node->next->str, 34))
				node->next->heredoc_quote = 1;
		}
		i = 0;
		while (node->str[i])
		{
			if (node->str[i] && node->str[i] != '$')
				create_nonvar_token(s, &i, &flag, node);
			if (node->str[i] == '$')
				create_var_token(s, &i, flag, node);
		}
		node = node->next;
	}
}
