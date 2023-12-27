/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 08:49:36 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 14:37:43 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_str(t_parsed *list)
{
	char	*arg;

	arg = NULL;
	if (list)
	{
		if (list->expand)
			arg = list->expand;
		else
			arg = list->str;
	}
	return (arg);
}

void	free_2d_array(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			if (ptr[i])
				free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

int	delimiter_char(char c)
{
	if (c == ' ' || c == '\0' || c == '|' || c == '<' 
		|| c == '>')
		return (1);
	return (0);
}

int	op_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	set_shlvl(char **dup)
{
	char	*tmp;
	char	*num;
	int		i;

	i = 0;
	while (dup[i])
	{
		if (!strncmp(dup[i], "SHLVL", 5))	
		{
			if (dup[i][5] == '\0' || (dup[i][5] == '=' && dup[i][6] == '\0'))
				//ft_setenv(&dup, "SHLVL=1");
			if (dup[i][5] == '=' && ft_isdigit(dup[i][6]))
			{
				num = ft_itoa(ft_atoi(ft_strchr(dup[i], '=') + 1) + 1);
				if (!num)
					free_and_exit(MALLOC_ERROR, NULL);
				tmp = ft_strjoin("SHLVL=", num);
				free(num);
				if (!tmp)
					free_and_exit(MALLOC_ERROR, NULL);
				//ft_setenv(&dup, tmp);
				free(tmp);
			}
		}
		i++;
	}
}

char	**dup_envp(char **envp)
{
	char	**dup;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		free_and_exit(MALLOC_ERROR, NULL);
	i = 0;
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

