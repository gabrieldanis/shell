/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:24:27 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 11:24:38 by gdanis           ###   ########.fr       */
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
		if (!ft_strncmp(str, s->env[i], ft_strlen(str)) &&
				s->env[i][ft_strlen(str)] == '='
				 && s->env[i][ft_strlen(str) + 1] != '\0')
		{
			return (s->env[i] + ft_strlen(str) + 1);
		}
		i++;
	}
	return (NULL);
}

