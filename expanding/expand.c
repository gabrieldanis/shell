/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:54:47 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/29 13:02:01 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	expand_token(t_shell *s)
{
	t_token	*tmp;
	t_token	*start;
	char	*var;
	char	*old_str;
	int		i;

	start = s->tlst->sp;
	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	token_addlstlast(&s->tlst->ex, tmp);
	while (s->tlst->sp)
	{
		if (ft_strchr(s->tlst->sp->str, '$')
				&& ft_strlen(s->tlst->sp->str) != 1 && s->tlst->sp->type)
		{
			var = ft_getenv(s->tlst->sp->str + 1, s);
			i = 0;
			while (var[i] && var[i] != ' ')
			{
				ft_charjoin(&last_token(s->tlst->ex)->str, var[i], s);
				i++;
			}
			if (var[i])
			{
				tmp = (t_token *)malloc(sizeof(t_token));
				*tmp = (t_token){0};
				token_addlstlast(&s->tlst->ex, tmp);
			// here create a new node 
			
			}
		}
		else if (ft_strchr(s->tlst->sp->str, '$')
				&& ft_strlen(s->tlst->sp->str) != 1)
		{
			var = ft_getenv(s->tlst->sp->str + 1, s);
			old_str = last_token(s->tlst->ex)->str;
			last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str, var);
			free(old_str);
		}
		else
		{
			old_str = last_token(s->tlst->ex)->str;
			last_token(s->tlst->ex)->str = ft_strjoin(last_token(s->tlst->ex)->str, s->tlst->sp->str);
			free(old_str);
		}
	}
	s->tlst->sp = start;
}
