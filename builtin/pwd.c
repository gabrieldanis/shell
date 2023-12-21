/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:45:08 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/21 10:55:55 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_pwd(void)
{
	char	path[500];

	if (getcwd(path, sizeof(path)) == NULL)
		return (error_message(GEN_ERROR, "pwd", NULL));
	printf("%s\n", path);
	return (0);
}
