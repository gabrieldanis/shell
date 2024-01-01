/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/31 09:34:38 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_getenv(char *str, t_shell *s)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (s->env[i])
	{
		if (!ft_strncmp(str, s->env[i], ft_strlen(str)) &&
				s->env[i][ft_strlen(str)] == '='
				 && s->env[i][ft_strlen(str) + 1] != '\0')
		{
			return (s->env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	return (NULL);
}

void	expand_token(t_shell *s)
{
	t_token	*tmp;
	t_token	*start;
	t_token	*tstart;
	char	*var;
	char	*old_str;
	int		i;

	start = s->tlst->sp;
	tstart = s->tlst;
	while (s->tlst)
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		*tmp = (t_token){0};
		token_addlstlast(&s->tlst->ex, tmp);
		while (s->tlst->sp)
		{
			if (ft_strchr(s->tlst->sp->str, '$')
				&& ft_strlen(s->tlst->sp->str) != 1 && s->tlst->sp->split)
			{
				var = ft_getenv(s->tlst->sp->str + 1, s);
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
						{
							tmp = (t_token *)malloc(sizeof(t_token));
							*tmp = (t_token){0};
							token_addlstlast(&s->tlst->ex, tmp);
						}
					}
				}
			}
			else if (ft_strchr(s->tlst->sp->str, '$')
					&& ft_strlen(s->tlst->sp->str) != 1)
			{
				if (s->tlst->sp->expand)
					var = ft_getenv(s->tlst->sp->str + 1, s);
				else
					var = s->tlst->sp->str;
				old_str = last_token(s->tlst->ex)->str;
				last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str, var);
				if (old_str)
					free(old_str);
			}
			else
			{
				old_str = last_token(s->tlst->ex)->str;
				last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str, s->tlst->sp->str);
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
