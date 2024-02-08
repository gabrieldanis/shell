/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:24:27 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/08 19:49:29 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_getenv(char *str, t_shell *s)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (s->env[i])
	{
		if (!ft_strncmp(str, s->env[i], ft_strlen(str))
			&& s->env[i][ft_strlen(str)] == '='
				&& s->env[i][ft_strlen(str) + 1] != '\0')
		{
			return (s->env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	return (NULL);
}

void	token_strjoin(char **s1, char **s2, t_shell *s)
{
	char	*old_str;

	old_str = *s1;
	*s1 = ft_strjoin(*s1, *s2);
	if (old_str)
		free(old_str);
	if (!*s1)
	{
		s->tlst->sp = s->sp_start;
		s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
}

char	*token_vardup(char *s1, t_shell *s, int itoa)
{
	char	*str;

	if (itoa)
		str = ft_itoa(s->rval);
	else
		str = ft_strdup(s1);
	if (!str)
	{
		s->tlst->sp = s->sp_start;
		s->tlst = s->t_start;
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	}
	return (str);
}
