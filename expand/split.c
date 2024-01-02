/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:00:53 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 11:32:26 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	split_token(t_shell *s) 
{
	t_token *start;
	int		flag;
	int		oldflag;
	int		i;

	flag = 0;
	oldflag = 0;
	start = s->tlst;
	while (s->tlst)
	{
		if (s->tlst->type == HEREDOC && s->tlst->next)
			s->tlst->next->type = HEREDOC_DEL; 
		i = 0;
		while (s->tlst->str[i])
		{
			if (s->tlst->str[i] && s->tlst->str[i] != '$')
			{
				if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
				{
					token_addlstlast(&s->tlst->sp);
				}
				while (s->tlst->str[i] && s->tlst->str[i] != '$')
				{
					setqflag(&flag, s->tlst->str[i]);
					if (oldflag == flag)
						ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
					oldflag = flag;
					i++;
				}
				if (!last_token(s->tlst->sp)->str)
					last_token(s->tlst->sp)->str = ft_strdup("");
	 		}
			if (s->tlst->str[i] == '$')
			{
				if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
				{
					token_addlstlast(&s->tlst->sp);
				}
				ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
				i++;
				while (check_is_var(s->tlst->str[i]))	
				{
					if (!flag && s->tlst->type != HEREDOC_DEL)
						last_token(s->tlst->sp)->split = 1;
					if ((flag == 2 || flag == 0) && s->tlst->type != HEREDOC_DEL)
						last_token(s->tlst->sp)->expand = 1;
					ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
					i++;
				}
			}
		}
		s->tlst = s->tlst->next;
	}
	s->tlst = start;
}
