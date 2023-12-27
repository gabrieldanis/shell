/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:51:30 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 11:01:54 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

void	operator_tokens(t_shell *s, int * flag, int *i)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	token_addlstlast(s, tmp);
	ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
	(*i)++;
	if (s->str[*i] == '<' && s->str[(*i) - 1] == '<')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
	}
	if (s->str[*i] == '>' && s->str[(*i) - 1] == '>')
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		(*i)++;
	}
	*flag = 0;
}

void	char_to_token(t_shell *s, int *flag, int *i)
{
	t_token	*tmp;

	if (*flag == 0)
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s);
		*tmp = (t_token){0};
		token_addlstlast(s, tmp);
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		if (!last_token(s->tlst)->str)
			free_and_exit(MALLOC_ERROR, s);
		*flag = 1;
	}
	else
	{
		ft_charjoin(&(last_token(s->tlst)->str), s->str[*i], s);
		if (!last_token(s->tlst)->str)
			free_and_exit(MALLOC_ERROR, s);
	}
	(*i)++;
}

void	space_to_token(t_shell *s, int *flag, int *i)
{
	t_token	*tmp;
	int	j;

	j = 0;
	while (s->str[*i] == ' ')
	{
		(*i)++;
		j++;
	}
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s);
	*tmp = (t_token){0};
	token_addlstlast(s, tmp);
	last_token(s->tlst)->str = (char *) malloc (sizeof(char) * (j + 1));
	if (!last_token(s->tlst)->str)
		free_and_exit(MALLOC_ERROR, s);
	ft_memset(last_token(s->tlst)->str, ' ', j);
	last_token(s->tlst)->str[j] = '\0';
	*flag = 0;
}

void	tokenizer(t_shell *s)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s->str[i])
	{
		if (s->str[i] == ' ')
			space_to_token(s, &flag, &i);
		if (s->str[i] == '|'|| s->str[i] == '<' || s->str[i] == '>'
			|| s->str[i] == '"' || s->str[i] == 39 || s->str[i] == '/' || s->str[i] == '.')
			operator_tokens(s, &flag, &i);
		if (s->str[i] != ' ' && s->str[i] != '\0' && s->str[i] != '|' && s->str[i] != '<' 
			&& s->str[i] != '>' && s->str[i] != '"' && s->str[i] != 39 && s->str[i] != '/' && s->str[i] != '.')
			char_to_token(s, &flag, &i);
	}
}
