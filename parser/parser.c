/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:37:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/13 20:06:58 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	delimiter_char(char c)
{
	if (c == ' ' || c == '\0' || c == '|' || c == '<' 
		|| c == '>' || c == '"' || c == 39)
		return (1);
	return (0);
}

int	op_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_parsed	*p_lstlast(t_parsed *list)
{
	while (list->next)
		list = list->next;	
	return (list);
}

t_parsed	*parser(t_token *list)
{
	t_parsed *plist;
	t_parsed *tmp;
	char	*old_str;
	plist = NULL;
	while (list)
	{
		while (list && list->str[0] != ' ')
		{
			if (op_char(list->str[0]))
			{
				tmp = (t_parsed *) malloc (sizeof(t_parsed));
				*tmp = (t_parsed){0};
				tmp->str = ft_strdup(list->str);
				if (!plist) 
					plist = tmp;
				else
					p_lstlast(plist)->next = tmp;
				list = list->next;
			}
			else if (list && (list->str[0] == '"' || list->str[0] == 39))
			{
				tmp = (t_parsed *) malloc (sizeof(t_parsed));
				*tmp = (t_parsed){0};
				tmp->str = ft_strdup(list->str);
				list = list->next;
				if (!plist) 
					plist = tmp;
				else
					p_lstlast(plist)->next = tmp;
				while (list && list->str[0] != p_lstlast(plist)->str[0])
				{
					old_str = p_lstlast(plist)->str;
					p_lstlast(plist)->str = ft_strjoin(p_lstlast(plist)->str, list->str);
					free(old_str);
					list = list->next;
				}
				if(list->str[0] == p_lstlast(plist)->str[0])
				{
					old_str = p_lstlast(plist)->str;
					p_lstlast(plist)->str = ft_strjoin(p_lstlast(plist)->str, list->str);
					free(old_str);
					list = list->next;
				}
				else
				{
					printf("error: unclosed quote");
					exit (1);
				}
			}
			else
			{
				tmp = (t_parsed *) malloc (sizeof(t_parsed));
				*tmp = (t_parsed){0};
				tmp->str = ft_strdup(list->str);
				list = list->next;
				if (!plist) 
					plist = tmp;
				else
					p_lstlast(plist)->next = tmp;
				while (list && !delimiter_char(list->str[0]))
				{
					old_str = p_lstlast(plist)->str;
					p_lstlast(plist)->str = ft_strjoin(p_lstlast(plist)->str, list->str);
					free(old_str);
					list = list->next;
				}
			}
		}
		if (list)
			list = list->next;

	}
	return (plist);
}

void	expand_quote(t_parsed *node)
{
	tmp->expand = 
}

t_parsed	*info_parsed_list(t_parsed *list)
{
	t_parsed	*tmp;
	int	i;

	tmp = list;
	i = 0;
	if (!(tmp->type >= 4 && tmp->type <= 8))
		tmp->type = 11;
	while (tmp)
	{
		tmp->idx = i;	
		i++;
		if (tmp->type == 7 && tmp->next)
			tmp->next->eof = 1;
		if (tmp->type == 3 && getenv(tmp->str + 1))
			tmp->expand = ft_strdup(getenv(tmp->str + 1));
		if (tmp->type == 9 || tmp->type == 10)
			expand_quote(tmp);
		tmp = tmp->next;
	}
	return (list);
}

t_parsed	*type_parsed_list(t_parsed *list)
{
	t_parsed	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->str[0] == '>' && tmp->str[1] == '\0')	
			tmp->type = 6;
		if (tmp->str[0] == '<' && tmp->str[1] == '\0')	
			tmp->type = 5;
		if (!ft_strncmp(tmp->str, "<<", 2))	
			tmp->type = 7;
		if (!ft_strncmp(tmp->str, ">>", 2))	
			tmp->type = 8;
		if (!ft_strncmp(tmp->str, "|", 1))	
			tmp->type = 4;
		if (!ft_strncmp(tmp->str, "-", 1) || !ft_strncmp(tmp->str, "--", 2))	
			tmp->type = 2;
		if (ft_strchr(tmp->str, '/') || ft_strchr(tmp->str, '.'))	
			tmp->type = 1;
		if (!ft_strncmp(tmp->str, "$", 1))	
			tmp->type = 3;
		if (!ft_strncmp(tmp->str, "\'", 1))	
			tmp->type = 9;
		if (!ft_strncmp(tmp->str, "\"", 1))	
			tmp->type = 10;
		tmp = tmp->next;
	}
	return (list);
}

char	*token_type(int i)
{
	if (i == 11)
		return ("command       ");
	if (i == 1)
		return ("file or dir   ");
	if (i == 2)
		return ("flag          ");
	if (i == 3)
		return ("variable      ");
	if (i == 4)
		return ("pipe          ");
	if (i == 5)
		return ("redirect in   ");
	if (i == 6)
		return ("redirect out  ");
	if (i == 7)
		return ("heredoc       ");
	if (i == 8)
		return ("append std out");
	if (i == 9)
		return ("single quote  ");
	if (i == 10)
		return ("double quote  ");
	return ("unknown       ");
}

void	print_parsed_list(t_parsed *list)
{
	while (list)
	{
		printf("type: %s\t:  ", token_type(list->type));
		printf("%s", list->str);
		printf("\n");
		if (list->type == 3)
			printf("var = %s\n", list->expand);
		if (list->eof)
			printf("EOF\n");
		list = list->next;
	}
}
