/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/14 12:30:54 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_token(t_shell *s)
{
	char	*var;
	int		i;

	s->sp_start = s->tlst->sp;
	s->t_start = s->tlst;
	while (s->tlst)
	{
		s->sp_start = s->tlst->sp;
		token_addlstlast(&s->tlst->ex, s);
		while (s->tlst->sp)
		{
			if (ft_strchr(s->tlst->sp->str, '$')
				&& ft_strlen(s->tlst->sp->str) != 1 && s->tlst->sp->split)
			{
				if (s->tlst->sp->str[1] == '?' && s->tlst->sp->str[2] == '\0')
					var = token_vardup(NULL, s, EXIT_VALUE);
				else
				{
					if (ft_getenv(s->tlst->sp->str + 1, s))
						var = token_vardup(ft_getenv(s->tlst->sp->str + 1, s), s, 0);
					else var = NULL;
				}
				i = 0;
				while (var && var[i])
				{
					while (var[i] && var[i] != ' ' && var[i] != '\t')
						ft_charjoin(&last_token(s->tlst->ex)->str, var[i++], s);
					if (var[i] == ' ' || var[i] == '\t')
					{
						while (var[i] == ' ' || var[i] == '\t')
							i++;
						if (var[i] && last_token(s->tlst->ex)->str)
							token_addlstlast(&s->tlst->ex, s);
					}
				}
				if (var)
					free(var);
			}
			else if (ft_strchr(s->tlst->sp->str, '$')
					&& (ft_strlen(s->tlst->sp->str) != 1
						|| (ft_strlen(s->tlst->sp->str) == 1 && !s->tlst->sp->expand)))
			{
				if (s->tlst->sp->expand)
				{
					if (s->tlst->sp->str[1] == '?' && s->tlst->sp->str[2] == '\0')
						var = token_vardup(NULL, s, EXIT_VALUE);
					else
						var = token_vardup(ft_getenv(s->tlst->sp->str + 1, s), s, 0);
				}
				else
					var = token_vardup(s->tlst->sp->str, s, 0);
				token_strjoin(&(last_token(s->tlst->ex)->str), &var, s);
				if (var)
					free (var);
			}
			else if (!(ft_strchr(s->tlst->sp->str, '$')
					&& ft_strlen(s->tlst->sp->str) == 1))
				token_strjoin(&(last_token(s->tlst->ex)->str), &(s->tlst->sp->str), s);
			s->tlst->sp = s->tlst->sp->next;
		}
		s->tlst->sp = s->sp_start;
		s->tlst = s->tlst->next;
	}
	s->tlst = s->t_start;
}
