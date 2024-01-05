/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/05 11:40:51 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_token(t_shell *s)
{
	t_token	*start;
	t_token	*tstart;
	char	*var;
	char	*old_str;
	int		i;

	start = s->tlst->sp;
	tstart = s->tlst;
	while (s->tlst)
	{
		token_addlstlast(&s->tlst->ex);
		while (s->tlst->sp)
		{
			if (ft_strchr(s->tlst->sp->str, '$')
				&& ft_strlen(s->tlst->sp->str) != 1 && s->tlst->sp->split)
			{
				if (s->tlst->sp->str[1] == '?' && s->tlst->sp->str[2] == '\0')
					var = ft_itoa(s->rval); 
				else
					var = ft_strdup(ft_getenv(s->tlst->sp->str + 1, s));
				i = 0;
				while (var && var[i])
				{
					while (var[i] && var[i] != ' ' && var[i] != '\t')
					{
						ft_charjoin(&last_token(s->tlst->ex)->str, var[i], s);
						i++;
					}
					if (var[i] == ' ' || var[i] == '\t')
					{
						while (var[i] == ' ' || var[i] == '\t')
							i++;
						if (var[i] && last_token(s->tlst->ex)->str)
							token_addlstlast(&s->tlst->ex);
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
						var = ft_itoa(s->rval); 
					else
						var = ft_strdup(ft_getenv(s->tlst->sp->str + 1, s));
				}
				else
					var = ft_strdup(s->tlst->sp->str);
				old_str = last_token(s->tlst->ex)->str;
				last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str, var);
				if (var)
					free (var);
				if (old_str)
					free(old_str);
			}
			else if (!(ft_strchr(s->tlst->sp->str, '$')
					&& ft_strlen(s->tlst->sp->str) == 1))
			{
				old_str = last_token(s->tlst->ex)->str;
				last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str,
						s->tlst->sp->str);
				if (old_str)
					free(old_str);
			}
			s->tlst->sp = s->tlst->sp->next;
		}
		s->tlst->sp = start;
		s->tlst = s->tlst->next;
		if (s->tlst)
			start = s->tlst->sp;
	}
	s->tlst = tstart;
}
