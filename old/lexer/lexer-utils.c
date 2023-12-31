/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:13:40 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/29 12:33:01 by gdanis           ###   ########.fr       */
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

/*
t_token	*last_token(t_token *t)
{
	while(t && t->next)
		t = t->next;	
	return (t);
}
void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}

void	token_addlstlast(t_shell *s, t_token *tmp)
{
	if (!s->tlst)
		s->tlst = tmp;
	else
		last_token(s->tlst)->next = tmp;
}
*/
