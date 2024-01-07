/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:06:51 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/07 17:06:00 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


//void	ft_pipe(t_shell *s)
void	ft_pipe()
{
	char	*str;
	char	buffer[10];
	int	id;
	int	fd[2];
	// fd[0] = read
	// fd[1] = write
	str = "bam";

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("pipe creation fucked", 2);
		//error_message(PIPE_ERROR, NULL, NULL, s);
		exit (1);
	}
	id = fork();
	if (id == -1)
	{
		ft_putendl_fd("fork fucked", 2);
		exit (1);
	}
	if (id == 0)
	{

		close(fd[0]);
		str = "wam";
		ft_putstr_fd(str, fd[1]);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		ft_putendl_fd(str, 1);
		read(fd[0], buffer, sizeof(int));
		printf("str: %s\n", str);
		printf("buffer: %s\n", buffer);
		close(fd[0]);
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_pipe();

	return (0);
}
