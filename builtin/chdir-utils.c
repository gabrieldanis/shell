/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:06:05 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/07 20:06:47 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*create_broken_pwd(t_shell *s, char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("PWD=", s->cwd);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	tmp2 = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = NULL;
	if (!tmp2)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	tmp = ft_strjoin(tmp2, str);
	free(tmp2);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	return (tmp);
}
