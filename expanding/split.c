/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:00:53 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/30 18:19:55 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

void	remove_lastsp_if_empty(t_token *lst)
{
	t_token	*tmp;
	t_token	*start;

	start = lst->sp;
	if (lst->sp && !last_token(lst->sp)->str)
	{
		if (!lst->sp->next)
		{
			free(lst->sp);
			lst->sp = NULL;
		}
		else
		{
			while(lst->sp->next->next)	
				lst->sp = lst->sp->next;	
			tmp = lst->sp;
			lst->sp = lst->sp->next;
			free(lst->sp);
			tmp->next = NULL;
			lst->sp = start;
		}
	}
}

void	split_token(t_shell *s) 
{
	t_token *start;
	t_token	*tmp;
	int		flag;
	int		oldflag;
	int		i;

	flag = 0;
	oldflag = 0;
	start = s->tlst;
	while (s->tlst)
	{
		i = 0;
		while (s->tlst->str[i])
		{
			if (s->tlst->str[i] && s->tlst->str[i] != '$')
			{
				if (!s->tlst->sp || (s->tlst->sp && last_token(s->tlst->sp)->str))
				{
					tmp = (t_token *)malloc(sizeof(t_token));
					*tmp = (t_token){0};
					token_addlstlast(&s->tlst->sp, tmp);
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
					tmp = (t_token *)malloc(sizeof(t_token));
					*tmp = (t_token){0};
					token_addlstlast(&s->tlst->sp, tmp);
				}
				ft_charjoin(&(last_token(s->tlst->sp)->str), s->tlst->str[i], s);
				i++;
				while (check_is_var(s->tlst->str[i]))	
				{
					if (!flag)
						last_token(s->tlst->sp)->split = 1;
					if (flag == 2 || flag == 0)
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
