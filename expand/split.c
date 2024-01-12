/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:00:53 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/12 17:29:02 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	split_token(t_shell *s) 
{
	int		flag;
	int		oldflag;
	int		i;

	flag = 0;
	oldflag = 0;
	s->t_start = s->tlst;
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
					token_addlstlast(&s->tlst->sp, s);
				while (s->tlst->str[i] && s->tlst->str[i] != '$')
				{
					setqflag(&flag, s->tlst->str[i]);
					if (oldflag == flag)
						ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
					oldflag = flag;
					i++;
				}
				if (!last_token(s->tlst->sp)->str)
				{
					last_token(s->tlst->sp)->str = ft_strdup("");
					if (!last_token(s->tlst->sp)->str)
						free_and_exit(MALLOC_ERROR, s);
				}
	 		}
			if (s->tlst->str[i] == '$')
			{
				if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
					token_addlstlast(&s->tlst->sp, s);
				ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
				i++;
					if (!flag && s->tlst->type != HEREDOC_DEL)
						last_token(s->tlst->sp)->split = 1;
					if ((flag == 2 || flag == 0) && s->tlst->type != HEREDOC_DEL
						&& (check_is_var(s->tlst->str[i]) || s->tlst->str[i] == '?'))
						last_token(s->tlst->sp)->expand = 1;
					if (flag == 0 && !check_is_var(s->tlst->str[i]))
						last_token(s->tlst->sp)->expand = 1;
				while (check_is_var(s->tlst->str[i]) || (s->tlst->str[i] == '?'
						&& s->tlst->str[i - 1] == '$'))	
				{
					ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
					i++;
					if (s->tlst->str[i - 1] == '?' && s->tlst->str[i - 2] == '$')
						break;
				}
			}
		}
		s->tlst = s->tlst->next;
	}
	s->tlst = s->t_start;
}
