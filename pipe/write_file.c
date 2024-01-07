/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:39:32 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/07 17:08:14 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_write(char *outfile)
{
	int	file;

	file = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file == -1)
	{
		ft_putstr_fd("fuck write to file failed\n", 2);
		exit (1);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit (1);
	}
	close(file);
}

void	ft_read(char *infile)
{
	int	file;

	file = open(infile, O_RDONLY);
	if (file == -1)
	{
		ft_putstr_fd("read failed\n", 2);
		exit (1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		exit (1);
	}
	close(file);
}


int	main(int argc, char *argv[])
{
	char	**cmd;
	int		pid;
	int		exit_status;

	if (argc < 3)
		return (printf("too few arguments\n"), 0);
	pid = fork();
	if (pid == -1)
		return (ft_putendl_fd("fucked up fork", 2), 1);
	if (pid == 0)
	{

		//redirecting read
		ft_read(argv[1]);

		//splitting commands and args
		cmd = ft_split(argv[2], ' ');

		//redirecting write
		if (argv[3])
			ft_write(argv[3]);

		// executing cmd
		if (execvp(cmd[0], cmd) == -1)
		{
			ft_putstr_fd("execvp failed\n", 2);
			exit (1);
		}
	}
	else
	{
		int	status;
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (!exit_status)	
				printf("noice\n");
			else
				printf("fuuck, child process exited with %d\n", exit_status);
		}
	}
	return (0);
}
