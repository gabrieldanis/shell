/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:37:21 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/16 12:33:06 by gdanis           ###   ########.fr       */
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
				if(list && list->str && list->str[0] == p_lstlast(plist)->str[0])
				{
					old_str = p_lstlast(plist)->str;
					p_lstlast(plist)->str = ft_strjoin(p_lstlast(plist)->str, list->str);
					free(old_str);
					list = list->next;
				}
				else
				{
					printf("error: unclosed quote\n");
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

char	*expand_var_in_quote(char *str)
{
	char	*tmp;
	char	*var_name;
	char	*var;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '$')
		i++;		
	while (str[i + j] && str[i + j] != ' ')
		j++;
	var_name = (char *) malloc (sizeof(char) * (j + 1));
	while (k < j)
	{
		var_name[k] = str[i + k];
		k++;
	}
	var_name[k] = '\0';
	while (str[i + j])
		i++;
	var = expand_var(var_name);
	tmp = (char *) malloc (sizeof(char) * (i + ft_strlen(var) + 1));
	k = 0;
	j = 0;
	while (str[k] != '$')
	{
		tmp[k] = str[k];
		k++;
	}
	while (j < (int)ft_strlen(var))
	{
		tmp[k + j]= var[j];
		j++;
	}
	while (str[k + ft_strlen(var_name)])
	{
		tmp[k + j] = str[k + ft_strlen(var_name)];
		k++;
	}
	free (var_name);
	tmp[k + j] = '\0';
	free (str);
	str = tmp;
	return (str);
}

void	expand_quote(t_parsed *node)
{
	int	dquote;

	dquote = 0;
	if (node->str[0] == '"')
	{
		node->expand = ft_strtrim(node->str, "\"");
		dquote = 1;
	}
	if (node->str[0] == 39)
		node->expand = ft_strtrim(node->str, "\'");
	if (ft_strchr(node->expand, '$') && dquote && !node->eof)
	{
		if (!ft_strchr(node->expand, '$'))
			return ;
		node->expand = expand_var_in_quote(node->expand);
	}

}

char	*expand_var(char *str)
{
	char	**split_str;
	char	*final_str;
	int	i;

	final_str = NULL;
	i = 0;
	split_str = ft_split(str, '$');
	if (!split_str)
		return (NULL);
	if (str[0] != '$')
		final_str = ft_strjoin(final_str, split_str[i++]);
	while (split_str[i])
		final_str = ft_strjoin(final_str, getenv(split_str[i++]));
	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
	if (*(strrchr(str, '$') + 1) == '\0')
		final_str = ft_strjoin(final_str, "$");
	return (final_str);
}

t_parsed	*info_parsed_list(t_parsed *list)
{
	t_parsed	*tmp;
	int	i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		tmp->idx = i;	
		i++;
		if (tmp->type == 7 && tmp->next)
			tmp->next->eof = 1;
		if (tmp->type == 3)
			tmp->expand = expand_var(tmp->str);
		if (tmp->type == 9 || tmp->type == 10)
			expand_quote(tmp);
		tmp = tmp->next;
	}
	list->type = 11;
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
		if (ft_strchr(tmp->str, '$'))	
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
		if (list->str)
			printf("%s", list->str);
		if (list->expand)
			printf(" -> %s", list->expand);
		printf("\n");
		if (list->eof)
			printf("EOF\n");
		list = list->next;
	}
}
