/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 22:27:36 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/30 17:53:57 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_charjoin(char **s1, char c, t_shell *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	if (*s1)
		len = ft_strlen(*s1);
	else
		len = 0;
	str = (char *) malloc ((sizeof(char)) * (len + 2));
	if (str == NULL)
		free_and_exit(MALLOC_ERROR, s);
	i = 0;
	while (*s1 && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = '\0';
	if (*s1)
		free(*s1);
	*s1 = str;
}

int	is_delimiter(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	operator_token(t_shell *s, int *i)
{
	t_token	*tmp;
	char	*ops;
	int	j;

	ops = "<>|";
	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	token_addlstlast(&s->tlst, tmp);
	j = 0;
	while (ops[j])
	{
		if (ops[j] == s->str[*i])
			break ;
		j++;
	}
	last_token(s->tlst)->type = j;
	ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
	(*i)++;
	if (s->str[*i] == '<' && s->str[(*i) - 1] == '<')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
		last_token(s->tlst)->type = 3;
	}
	if (s->str[*i] == '>' && s->str[(*i) - 1] == '>')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
		last_token(s->tlst)->type = 4;
	}
}

void	str_to_token(t_shell *s)
{
	t_token	*tmp;
	int	flag;
	int	i;
	
	flag = 0;
	i = 0;
	while (s->str[i])
	{
		while (s->str[i] && (s->str[i] == ' ' || s->str[i] == '\t'))
			i++;	
		if ((s->str[i] == '<' || s->str[i] == '>' || s->str[i] == '|') && !flag)
			operator_token(s, &i);
		if (s->str[i] && !is_delimiter(s->str[i]))
		{
			tmp = (t_token *)malloc(sizeof(t_token));
			*tmp = (t_token){0};
			token_addlstlast(&s->tlst, tmp);
			while (s->str[i] && (!is_operator(s->str[i]) || flag))
			{
				setqflag(&flag, s->str[i]);
				ft_charjoin(&(last_token(s->tlst)->str), s->str[i], s);
				i++;
				if (!flag && (s->str[i] == ' ' || s->str[i] == '\t'))
					break;
			}
		}
	}
}
