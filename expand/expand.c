/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/13 18:53:05 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	create_space_token(t_shell *s, int *i, char *var)
{
	if (var[*i] == ' ' || var[*i] == '\t')
	{
		while (var[*i] == ' ' || var[*i] == '\t')
			(*i)++;
		//if (var[*i] && last_token(s->tlst->ex)->str)
		if (last_token(s->tlst->ex)->str)
			token_addlstlast(&s->tlst->ex, s);
	}
}

void	expand_splittable_vars(t_shell *s)
{
	int		i;

	if (s->tlst->sp->str[1] == '?' && s->tlst->sp->str[2] == '\0')
		s->var = token_vardup(NULL, s, EXIT_VALUE);
	else
	{
		if (ft_getenv(s->tlst->sp->str + 1, s))
			s->var = token_vardup(ft_getenv(s->tlst->sp->str + 1, s), s, 0);
		else
			s->var = NULL;
	}
	i = 0;
	while (s->var && s->var[i])
	{
		while (s->var[i] && s->var[i] != ' ' && s->var[i] != '\t')
			ft_charjoin(&last_token(s->tlst->ex)->str, s->var[i++], s);
		create_space_token(s, &i, s->var);
	}
	if (s->var)
	{
		free(s->var);
		s->var = NULL;
	}
}

void	expand_nonsplittable_vars(t_shell *s)
{
	char	*var;

	var = NULL;
	if (s->tlst->sp->expand)
	{
		if (s->tlst->sp->str[1] == '?' && s->tlst->sp->str[2] == '\0')
			var = token_vardup(NULL, s, EXIT_VALUE);
		else
		{
			if (ft_getenv(s->tlst->sp->str + 1, s))
				var = token_vardup(ft_getenv(s->tlst->sp->str + 1, s), s, 0);
		}
	}
	else
		var = token_vardup(s->tlst->sp->str, s, 0);
	token_strjoin(&(last_token(s->tlst->ex)->str), &var, s);
	if (var)
		free (var);
}

void	expand_token(t_shell *s)
{
	s->sp_start = s->tlst->sp;
	s->t_start = s->tlst;
	while (s->tlst)
	{
		s->sp_start = s->tlst->sp;
		token_addlstlast(&s->tlst->ex, s);
		if (s->tlst && s->tlst->ex && s->tlst->ex->next == NULL)
			s->ex_start = s->tlst->ex;
		while (s->tlst->sp)
		{
			if (ft_strchr(s->tlst->sp->str, '$') && ft_strlen(s->tlst->sp->str)
				!= 1 && s->tlst->sp->split)
				expand_splittable_vars(s);
			else if (ft_strchr(s->tlst->sp->str, '$') && (ft_strlen(
						s->tlst->sp->str) != 1 || (ft_strlen(s->tlst->sp->str)
						== 1 && !s->tlst->sp->expand)))
				expand_nonsplittable_vars(s);
			else if (!(ft_strchr(s->tlst->sp->str, '$')
					&& ft_strlen(s->tlst->sp->str) == 1))
				token_strjoin(&(last_token(s->tlst->ex)->str),
					&(s->tlst->sp->str), s);
			s->tlst->sp = s->tlst->sp->next;
		}
		s->tlst->sp = s->sp_start;
		s->tlst = s->tlst->next;
	}
	s->tlst = s->t_start;
}
