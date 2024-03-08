/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:14:54 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/08 13:53:56 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_env(t_shell *s, t_parsed *node)
{
	int	i;

	if (node->arglst[1])
	{
		errno = 2;
		return (error_message(ENV_ERROR, "env", node->arglst[1], s, errno));
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
