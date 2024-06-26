/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:49:31 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/08 12:52:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

/*********************************
 * 	INCLUDES
 *********************************/

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <string.h> 
# include <limits.h>
# include <ctype.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h> 
# include <sys/ioctl.h>
# include <errno.h>

/*********************************
 * 	GLOBAL VARIABLE
 *********************************/

extern int	g_var;

/*********************************
 * 	ERROR CODES
 *********************************/

# define MALLOC_ERROR			1
# define QUOTE_ERROR 			2 /* unclosed quote */
# define IDENT_ERROR 			3
# define GEN_ERROR				4
# define NOFILE_ERROR			5
# define CMD_ERROR				6
# define EXECVE_ERROR			7
# define FORK_ERROR				8
# define UNEX_TOKEN				9
# define ARGNUM_ERROR			10
# define NUM_ERROR				11
# define PIPE_ERROR				12
# define PID_ERROR				13
# define DUP_ERROR				14
# define WRITE_ERROR			15
# define PERM_ERROR				16
# define READ_ERROR				17
# define RL_ERROR				18
# define OPEN_ERROR				19
# define UNLINK_ERROR			20
# define HEREDOC_EOF_ERROR		21
# define ISDIR_ERROR			22
# define ENV_ERROR				23
# define NOINFILE_ERROR			24
# define OUTFILE_ERROR			25
# define NOCDFILE_ERROR			26
# define NOHOME_ERROR			27
# define SIG_ERROR				28
# define WAITPID_ERROR			29
# define OPTION_ERROR			30

/*********************************
 * 	PARSER CATEGORIES
 *********************************/

# define RED_IN			1 /* < */
# define RED_OUT		2 /* > */
# define PIPE			3 /* | */
# define HEREDOC		4 /* << */
# define RED_APP		5 /* >> */
# define HEREDOC_DEL	6 /* << "___" */
# define CMD			7
# define ARG			8
# define FILE_DIR		9
# define EXIT_VALUE		10
# define INFILE			11
# define OUTFILE		12

/*********************************
 * 	SIGNAL NUMS
 *********************************/

# define SIG_RL			0
# define SIG_MAIN		1
# define SIG_CHILD		2
# define SIG_HEREDOC	3

/*********************************
 * 	STRUCTS
 *********************************/

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*sp;
	struct s_token	*ex;
	char			*str;
	int				split;
	int				expand;
	int				heredoc_quote;
	int				type;
}	t_token;

typedef struct s_parsed
{
	struct s_parsed	*next;
	struct s_parsed	*lst;
	char			**arglst;
	char			**outfiles;
	char			*infile;
	char			*str;
	int				idx;
	int				type;
	int				eof;
	int				fd_inf;
	int				fd_outf;
	char			*cmd;
	int				cmd_found;
	char			**dirs;
	char			**dirs2;
	int				index;
	int				append;
	pid_t			pid;
	char			*filename;
	char			*last_heredoc;
	int				heredoc_quote;
}	t_parsed;

typedef struct s_shell
{
	t_parsed	*lst;
	t_token		*tlst;
	char		**argv;
	char		**env;
	char		*path;
	char		*str;
	char		*var;
	char		*cwd;
	int			**pipes;
	int			rval;
	int			cmds;
	int			heredocfd;
	int			j_value;
	int			builtin;
	int			error;
	int			outfile_error;
	int			running_child;
}	t_shell;

/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

t_shell		*init_shell(int argc, char **argv, char **envp);
t_parsed	*info_parsed_list(t_parsed *list);
t_parsed	*type_parsed_list(t_parsed *list);
t_parsed	*p_lstlast(t_parsed *list);
t_token		*last_token(t_token *t);
void		token_strjoin(char **s1, char **s2, t_shell *s);
void		expander(t_shell *s);
void		parser(t_shell *s);
void		token_addlstlast(t_token **lst, t_shell *s);
void		tokenizer(t_shell *s);
void		print_parsed_list(t_shell *s);
void		ft_charjoin(char **s1, char c, t_shell *s);
void		print_token(t_shell *s);
void		idx_tokens(t_token *list);
void		print_parsed_tokens(t_token *list);
void		type_tokens(t_token *list);
void		block_tokens(t_token *list);
void		execute(t_shell *s);
void		sort_var_list(char **dup);
void		ft_print_export_lines(char **dup, int i, int j);
void		free_2d_array(void **ptr);
void		set_q_flag(t_token *list, int *q_flag, char *quotes);
void		free_and_exit(int n, t_shell *s, char *exe, char *str);
void		plist_strjoin(t_shell *s, int *q_flag, char *quotes);
void		plist_add_to_last(t_parsed **tmp, t_shell *s);
void		plist_add_to_last_ex(t_parsed **tmp, t_shell *s);
void		set_q_flag_ex(t_parsed *list, int *q_flag, char *quotes, int *i);
void		set_sq_flag(int *sq_flag, char c);
void		set_q_flag_plist(t_parsed *list, int *q_flag, char *quotes);
void		remove_quotes(t_shell *s);
void		free_token_list(t_token *tlst);
void		free_parsed_list(t_parsed *list);
//void		handle_sig1(int sig, siginfo_t *info, void *ucontext);
void		handle_sig1(int signal_num);
void		handle_sig2(int signal_num);
void		ft_signal_heredoc(t_shell *s);
void		handle_sig1_heredoc(int signal_num);
//void		handle_sig2(int sig, siginfo_t *info, void *ucontext);
void		init_signals(struct sigaction sig1, struct sigaction sig2);
void		set_shlvl(t_shell *s);
void		ft_signal(t_shell *s);
void		handle_sig_child_1(int signal_num);
void		handle_sig_child_2(int signal_num);
void		child_signal(t_shell *s);
int			str_to_token(t_shell *s);
void		setqflag(int *flag, char c);
void		split_token(t_shell *s);
void		expand_token(t_shell *s);
void		exit_child(int n, t_shell *s);
void		arg_list(t_shell *s);
void		no_pipe(t_shell *s);
void		init_plst(t_shell *s);
void		ex_node_loop(t_shell *s, t_token *ex_node, t_token *t_node);
void		printlst(t_shell *s);
void		parse_type(t_shell *s);
int			parse_lstiter(t_shell *s,
				int (*f)(t_parsed *node, t_parsed *subnode, t_shell *s));
void		parse_subiter(t_shell *s,
				t_parsed *node, int (*f)(t_parsed *lst, t_shell *s));
void		create_tmp_file(t_parsed *node, t_shell *s);
void		delete_files(t_shell *s);
void		ft_unset_str(t_shell *s, char *str, int i);
void		free_lsts(t_shell *s);
void		ft_exit(t_shell *s, t_parsed *lst);
void		free_2d_array_i(void ***arr, int i);
void		free_s_str(t_shell *s);
void		node_dup(t_parsed *node, t_token *t_node, char *s2, t_shell *s);
char		*get_path(char **env);
char		*get_dir(char *str, t_shell *s);
char		**dup_envp(char **envp, t_shell *s);
char		*token_type(int i);
char		*expand_var(char *str);
char		*get_str(t_parsed *list);
char		*ft_getenv(char *str, t_shell *s);
char		*token_vardup(char *s1, t_shell *s, int itoa);
char		*heredoc_expand(char *line, t_shell *s);
char		*create_fstr(t_shell *s, char *fstr, char *str, char *line);
void		create_var_name(t_shell *s, char *line, char **str, int *i);
char		*get_next_line(int fd);
int			update_existing_var(t_shell *s, char *str);
int			append_var(t_shell *s, char *str);
int			ft_echo(t_parsed *list);
int			error_message(int n, char *exe_name, char *str, t_shell *s);
int			isenvar(char *env, char *varname);
int			parse_isfile(t_parsed *node, t_parsed *subnode, t_shell *s);
int			parse_heredoc(t_parsed *node, t_parsed *subnode, t_shell *s);
int			clear_screen(void);
int			ft_pwd(t_shell *s);
int			ft_setenv(t_shell *s, char *str);
int			is_varname(char *str);
int			ft_chdir(t_shell *s, t_parsed *lst);
int			ft_env(t_shell *s, t_parsed *lst);
int			ft_export(t_shell *s, t_parsed *lst, int env);
int			ft_print_export(char **envp, t_shell *s);
int			delimiter_char(char c);
int			op_char(char c);
int			check_is_var(char c);
int			ft_unset(t_shell *s, t_parsed *lst);
int			parse_cmdargs(t_parsed *node, t_parsed *subnode, t_shell *s);
int			is_delimiter(char c);
int			is_operator(char c);
int			arglst_size(t_parsed *lst);
int			check_builtin(char *str);
int			execute_builtin(t_shell *s, t_parsed *node);
int			syntax_check(t_shell *s);
int			check_eof(t_shell *s, t_token *node);
int			check_pipe(t_shell *s, t_token *node);
int			check_infiles(t_shell *s, t_parsed *lst);
void		multi_child_process(t_parsed *lst, t_shell *s, int ind);
void		child_process_error_check(t_shell *s, t_parsed *node);
char		*get_path(char **env);
void		free_array(char **arr);
int			multi_pipe(t_shell *s);
void		fd_closer(t_shell *s);
void		fd_opener(t_parsed *lst, t_shell *s);
void		multi_parent(t_parsed *lst);
void		child_processes(t_parsed *lst, t_shell *s, int ind);
void		wait_for_child(t_shell *s);
void		free_list(t_parsed *lst);
int			get_dir_multi(t_shell *s);
char		**get_dirs(t_shell *s, char **dirs);
void		check_arglst(t_shell *s, t_parsed *node, char **dirs);
void		free_cmd_dirs(t_shell *s, char **dirs, char *cmd);
void		check_absolute_path(t_shell *s, t_parsed *node, char **dirs);
char		*join_slash(t_shell *s, t_parsed *node, char **dirs, char *cmd);
void		check_for_dir(t_shell *s, t_parsed *node, char **dirs, char *cmd);
t_parsed	*get_to_node(t_parsed *node, int ind);
void		pipe_array(t_shell *s);
char		*ft_strjoin3(char *str1, char *str2, char *str3);
void		dir_copy(t_shell *s, int *ex, int i);
void		pipe_fork(t_parsed *lst, t_shell *s);
void		close_all_pipes(t_shell *s);
void		appln_chararr(t_parsed *lst, char *str, t_shell *s);
void		free_tmp_exit(char **tmp, t_shell *s);
void		count_parsed_nodes(t_shell *s);
void		ft_write_to_file(t_shell *s, t_parsed *node);
int			create_outfiles(t_shell *s);
void		print_env(char **env);
void		set_shell(t_shell *s);
t_parsed	*lstlast(t_parsed *lst);
void		free_parsed_list_strings(t_parsed *tmp);
void		shlvl_one(t_shell *s, char *tmp, int checker);
void		ft_getcwd(t_shell *s, char **path_var);
void		malloc_dup(t_shell *s, char ***dup, char **envp);
void		open_heredoc_fd(t_shell *s, t_parsed *subnode);
void		free_heredoc(t_shell *s, t_parsed *subnode, char *line);
char		*heredoc_read(char *line);
int			heredoc_break(t_shell *s, t_parsed *subnode, char *line);
int			_error(t_shell *s, t_parsed *subnode, char *line);
char		*copy_to_str(char *s1, char *s2, char *new_str);
char		*get_next_line(int fd);
char		*set_zero(char *str, size_t rread, int *i, char **nullme);
char		*malloc_size_i(int i);
char		*conc(char *mem, char *str, int *i, int len);
int			len(char *str, int rread, int i, int checker);
int			check_str_nl(char *str, unsigned long rread);
void		custom_message_quote_error(t_shell *s, int n);
void		check_cmd(t_shell *s, char **dirs, t_parsed *node);
int			check_outfile_access(char *str, char *str2, t_shell *s);
int			check_eof_error(t_shell *s, t_parsed *subnode, char *line);
int			create_node_outfiles(t_shell *s, t_parsed *lst);
char		*create_broken_pwd(t_shell *s, char *str);
void		signal_while_child(t_shell *s);
int			is_running_child(int num);
void		signal_handler(int num);
void		ident_error_check(t_shell *s, char *str);
void		call_execve(t_shell *s, t_parsed *node);

#endif
