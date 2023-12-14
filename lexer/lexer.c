/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:51:30 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/14 10:19:29 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

void	operator_tokens(t_token **list, int * flag, int *i, char *str)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	if (!(*list))
		*list = tmp;
	else
		last_token(*list)->next = tmp;
	ft_charjoin(&(last_token(*list)->str), str[*i]);
	(*i)++;
	if (str[*i] == '<' && str[(*i) - 1] == '<')
	{
		ft_charjoin(&(last_token(*list)->str), str[*i]);
		(*i)++;
	}
	if (str[*i] == '>' && str[(*i) - 1] == '>')
	{
		ft_charjoin(&(last_token(*list)->str), str[*i]);
		(*i)++;
	}
	*flag = 0;
}

void	char_to_token(t_token **list, int *flag, int *i, char *str)
{
	t_token	*tmp;

	if (*flag == 0)
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		*tmp = (t_token){0};
		if (!(*list))
			*list = tmp;
		else
			last_token(*list)->next = tmp;
		ft_charjoin(&(last_token(*list)->str), str[*i]);
		*flag = 1;
	}
	else
		ft_charjoin(&(last_token(*list)->str), str[*i]);
	(*i)++;
}

void	space_to_token(t_token **list, int *flag, int *i, char *str)
{
	t_token	*tmp;
	int	j;

	j = 0;
	while (str[*i] == ' ')
	{
		(*i)++;
		j++;
	}
	tmp = (t_token *)malloc(sizeof(t_token));
	*tmp = (t_token){0};
	if (!(*list))
		*list = tmp;
	else
		last_token(*list)->next = tmp;
	last_token(*list)->str = (char *) malloc (sizeof(char) * (j + 1));
	ft_memset(last_token((*list))->str, ' ', j);
	last_token((*list))->str[j] = '\0';
	*flag = 0;
}

t_token	*tokenizer(char *str)
{
	t_token	*list;
	int		i;
	int		flag;

	list = NULL;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			space_to_token(&list, &flag, &i, str);
		if (str[i] == '|'|| str[i] == '<' || str[i] == '>'
			|| str[i] == '"' || str[i] == 39 || str[i] == '/' || str[i] == '.')
			operator_tokens(&list, &flag, &i, str);
		if (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '<' 
			&& str[i] != '>' && str[i] != '"' && str[i] != 39 && str[i] != '/' && str[i] != '.')
			char_to_token(&list, &flag, &i, str);
	}
	return (list);
}
