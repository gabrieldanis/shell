/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:14:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/14 15:32:17 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_path(t_shell *s)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		if (!ft_strncmp(s->env[i], "PATH=", 5))	
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(t_shell *s, t_parsed *node)
{
	int	i;

	if (!check_path(s))
	{
		errno = 2;
		return (error_message(NOFILE_ERROR, "env", NULL, s));
	}
	if (node->arglst[1])
	{
		errno = 2;
		return (error_message(ENV_ERROR, "env", node->arglst[1], s));
	}
	i = 0;
	while (s->env[i])
	{
		if (ft_strchr(s->env[i], '='))
			printf("%s\n", s->env[i]);
		i++;
	}
	return (0);
}
