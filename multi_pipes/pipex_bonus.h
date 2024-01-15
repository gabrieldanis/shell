/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 00:01:20 by dberes            #+#    #+#             */
/*   Updated: 2024/01/05 15:27:52 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

typedef struct s_plist
{
	int					index;
	int					fd[2];
	pid_t				pid;
	struct s_plist		*next;
}	t_plist;

typedef struct s_data
{
	int		pipes;
	int		argc;
	int		fd_inf;
	int		fd_outf;
	char	*path;
	char	**env;
	char	**argv;
	char	**dirs;
	char	*cmd;
	char	**dirs2;
}	t_data;

void	first_child_process(t_plist **lst, t_data *data, int ind);
void	multi_child_process(t_plist **lst, t_data *data, int ind);
void	last_child_process(t_plist **lst, t_data *data, int ind);
void	multi_parent_process(t_plist **lst, t_data *data, int ind);
char	*get_path(char **env);
void	free_array(char **arr);
int		multi_pipe(int pipes, char **argv, char **env, int argc);
void	add_pipe_node(t_plist **lst, t_plist *new);
int		list_size(t_plist **lst);
void	fd_closer(int end, t_plist **lst);
void	multi_parent(t_plist *lst);
void	child_processes(t_plist **lst, t_data *data, int ind);
void	wait_for_child(t_plist *lst);
void	free_list(t_plist *lst);
char	*get_dir_multi(char *str, char **args, t_data *data);
void	check_commands_bonus(t_data *data, int *ex);
void	free_exit(char **args, t_data *data, char **dirs, int ex_code);
t_plist	*get_to_node(t_plist *node, int ind);
void	dirs_calloc(t_data *data);
void	path_error(t_data *data);
void	check_args(t_data *data, int *ex);
void	set_data_bonus(t_data *data, int pipes, char **argv, char **env);
void	file_create(t_data *data);
char	*ft_strjoin3(char *str1, char *str2, char *str3);
void	dup_fail(char **args, t_data *data, int fd, t_plist **lst);
void	fd_fail(char **args, t_data *data, int fd, t_plist **lst);
void	dir_copy(char **args, t_data *data, int *ex, int i);
void	print_fd_error(t_data *data);

#endif
