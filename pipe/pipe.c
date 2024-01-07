/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:06:51 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/06 23:15:10 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

//void	ft_pipe(t_shell *s)
int	ft_pipe(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("pipe creation fucked\n");
		//error_message(PIPE_ERROR, NULL, NULL, s);
		return (1);
	}

	return (0);
}

int	main(void)
{


	return (0);
}
