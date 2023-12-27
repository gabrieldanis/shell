/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 08:49:36 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 21:26:10 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	set_shlvl(t_shell *s)
{
	char	*tmp;
	char	*num;
	int		i;

	i = 0;
	while (s->env[i])
	{
		if (!strncmp(s->env[i], "SHLVL", 5))	
		{
			if (s->env[i][5] == '\0' || (s->env[i][5] == '=' && s->env[i][6] == '\0'))
				ft_setenv(s, "SHLVL=1");
			if (s->env[i][5] == '=' && ft_isdigit(s->env[i][6]))
			{
				num = ft_itoa(ft_atoi(ft_strchr(s->env[i], '=') + 1) + 1);
				if (!num)
					free_and_exit(MALLOC_ERROR, s);
				tmp = ft_strjoin("SHLVL=", num);
				free(num);
				if (!tmp)
					free_and_exit(MALLOC_ERROR, s);
				ft_setenv(s, tmp);
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

