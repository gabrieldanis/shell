/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:00:53 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/13 18:23:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	create_nonvar_token(t_shell *s, int *i, int *flag)
{
	static int		oldflag;

	if (s->tlst && s->tlst->sp && s->tlst->sp->next == NULL)
		s->sp_start = s->tlst->sp;
	if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
		token_addlstlast(&(s->tlst->sp), s);
	while (s->tlst->str[*i] && s->tlst->str[*i] != '$')
	{
		setqflag(flag, s->tlst->str[*i]);
		if (oldflag == *flag)
			ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[*i], s);
		oldflag = *flag;
		(*i)++;
	}
	if (!last_token(s->tlst->sp)->str)
	{
		last_token(s->tlst->sp)->str = ft_strdup("");
		if (!last_token(s->tlst->sp)->str)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	}
}

void	check_nonvarname_char(t_shell *s, int *i, int *non_varname_char)
{
	if (!check_is_var(s->tlst->str[*i]) && s->tlst->str[*i] != '?'
			&& s->tlst->str[*i] != '\0' && s->tlst->str[*i] != '"'
			&& s->tlst->str[*i] != 39 && s->tlst->str[*i] != ' '
			&& s->tlst->str[*i] != '=')
	{
		*non_varname_char = 1;
		last_token(s->tlst->sp)->expand = 0;
		last_token(s->tlst->sp)->split = 0;
	}
}

void	create_var_token(t_shell *s, int *i, int flag)
{
	int	non_varname_char;

	if (s->tlst && s->tlst->sp && s->tlst->sp->next == NULL)
		s->sp_start = s->tlst->sp;
	non_varname_char = 0;
	if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
		token_addlstlast(&s->tlst->sp, s);
	ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[*i], s);
	(*i)++;
	if (!flag && s->tlst->type != HEREDOC_DEL)
		last_token(s->tlst->sp)->split = 1;
	if ((flag == 2 || flag == 0) && s->tlst->type != HEREDOC_DEL
		&& (check_is_var(s->tlst->str[*i]) || s->tlst->str[*i] == '?'))
		last_token(s->tlst->sp)->expand = 1;
	if (flag == 0 && !check_is_var(s->tlst->str[*i]) && s->tlst->str[*i] != '\0')
		last_token(s->tlst->sp)->expand = 1;
	check_nonvarname_char(s, i, &non_varname_char);
	while (check_is_var(s->tlst->str[*i]) || (s->tlst->str[*i] == '?'
			&& s->tlst->str[(*i) - 1] == '$') || non_varname_char)
	{
		ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[*i], s);
		(*i)++;
		if ((s->tlst->str[(*i) - 1] == '?' && s->tlst->str[(*i) - 2] == '$') ||
		(non_varname_char && (!s->tlst->str[*i] || is_delimiter(*i) || s->tlst->str[*i] == '$')))
			break ;
		if ((s->tlst->str[*i] == '"' && flag == 2) || (s->tlst->str[*i] == 39 && flag == 1) ||
				(flag == 0 && (s->tlst->str[*i] == '"' || s->tlst->str[*i] == 39)))
			break;
	}
}

void	split_token(t_shell *s)
{
	int		flag;
	int		i;

	flag = 0;
	s->t_start = s->tlst;
	while (s->tlst)
	{
		if (s->tlst->type == HEREDOC && s->tlst->next)
		{
			s->tlst->next->type = HEREDOC_DEL;
			if (ft_strchr(s->tlst->next->str, '\'') ||
				ft_strchr(s->tlst->next->str, 34))
				s->tlst->next->heredoc_quote = 1;
		}
		i = 0;
		while (s->tlst->str[i])
		{
			if (s->tlst->str[i] && s->tlst->str[i] != '$')
				create_nonvar_token(s, &i, &flag);
			if (s->tlst->str[i] == '$')
				create_var_token(s, &i, flag);
		}
		s->tlst = s->tlst->next;
	}
	s->tlst = s->t_start;
}
