/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_old.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:46:37 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 14:46:47 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	free_2d_array((void **)split_str);
	if (strrchr(str, '$') && *(strrchr(str, '$') + 1) == '\0')
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
		if (tmp->type == 9 || tmp->type == 10)
			expand_quote(tmp);
		else if (ft_strchr(tmp->str, '$'))
			tmp->expand = expand_var(tmp->str);
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
		/*
		if (ft_strchr(tmp->str, '$'))	
			tmp->type = 3;
			*/
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
