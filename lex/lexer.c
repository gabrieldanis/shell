/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 22:27:36 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/21 11:56:24 by gdanis           ###   ########.fr       */
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
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
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

void	operator_token(t_shell *s, int *i)
{
	token_addlstlast(&s->tlst, s);
	if (s->str[*i] == '<')
		last_token(s->tlst)->type = RED_IN;
	if (s->str[*i] == '>')
		last_token(s->tlst)->type = RED_OUT;
	if (s->str[*i] == '|')
		last_token(s->tlst)->type = PIPE;
	ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
	(*i)++;
	if (s->str[*i] == '<' && s->str[(*i) - 1] == '<')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
		last_token(s->tlst)->type = HEREDOC;
	}
	if (s->str[*i] == '>' && s->str[(*i) - 1] == '>')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
		last_token(s->tlst)->type = RED_APP;
	}
}

void	non_operator_token(t_shell *s, int *i, int *flag)
{
	token_addlstlast(&s->tlst, s);
	while (s->str[*i] && (!is_operator(s->str[*i]) || *flag))
	{
		setqflag(flag, s->str[*i]);
		ft_charjoin(&(last_token(s->tlst)->str), s->str[(*i)++], s);
		if (!(*flag) && (s->str[*i] == ' ' || s->str[*i] == '\t'))
			break ;
	}
}

int	str_to_token(t_shell *s)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (s->str[i])
	{
		while (s->str[i] && (s->str[i] == ' ' || s->str[i] == '\t'))
			i++;
		if (is_operator(s->str[i]) && !flag)
			operator_token(s, &i);
		if (s->str[i] && !is_delimiter(s->str[i]))
			non_operator_token(s, &i, &flag);
	}
	if (flag)
	{
		error_message(QUOTE_ERROR, NULL, NULL, s);
		return (1);
	}
	return (0);
}
