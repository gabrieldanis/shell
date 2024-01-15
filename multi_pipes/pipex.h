/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:18:20 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 14:02:05 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> 
# include <stdio.h> 
# include <string.h> 
# include <stdlib.h>
# include <limits.h>
# include <ctype.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	int		pipes;
	int		argc;
	char	*path;
	char	**env;
	char	**argv;
	char	**dirs;
}	t_data;

void	child_process(int fd[2], t_data *data, int ind);
void	parent_process(int fd[2], t_data *data, int ind);
char	*get_path(char **env);
char	*get_dir(char *str, char **args, t_data *data);
void	free_array(char **arr);
int		single_pipe(char **argv, char **env);
int		multi_pipe(int pipes, char **argv, char **env, int argc);
char	*get_dir_multi(char *str, char **args, t_data *data);
void	check_commands(char **args, t_data *data, int ind);
void	free_exit(char **args, t_data *data, int ex_code);
void	dirs_calloc(t_data *data);
int		check_args_fd_out(char **args, t_data *data, int fd[2], int *ex);
int		check_args_fd_in(char **args, t_data *data, int fd[2], int *ex);
void	set_data(t_data *data, int pipes, char **argv, char **env);
void	free_exit_commands(char **args, t_data *data, int ex_code);
void	file_create(t_data *data);
void	free_exit_execve_malloc(char **args, t_data *data, int ex_code);
char	*make_cmd(char **args, char **dirs, t_data *data);
void	free_dirs(char **arr);
char	*ft_strjoin3(char *str1, char *str2, char *str3);
void	dup_fail(char **args, t_data *data, int fd, int fd_file);

#endif
