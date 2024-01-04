/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:45:08 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/04 11:11:57 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_pwd(t_shell *s)
{
	char	path[500];

	if (getcwd(path, sizeof(path)) == NULL)
		return (error_message(GEN_ERROR, "pwd", NULL, s));
	printf("%s\n", path);
	return (0);
}
