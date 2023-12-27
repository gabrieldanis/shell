/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:49:31 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 22:20:42 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "../libft/libft.h"

/*********************************
 * 	GLOBAL VARIABLE
 *********************************/


/*********************************
 * 	ERROR CODES
 *********************************/

# define MALLOC_ERROR 1
# define QUOTE_ERROR 2
# define IDENT_ERROR 3
# define GEN_ERROR 4
# define NOFILE_ERROR 5
# define CMD_ERROR 6
# define EXECVE_ERROR 7


/*********************************
 * 	PARSER CATEGORIES
 *********************************/

/*********************************
 * 	STRUCTS
 *********************************/

typedef struct s_token
{
	struct s_token	*next;
	char			*str;
}	t_token;

typedef struct s_parsed
{
	struct s_parsed	*next;
	struct s_parsed	*ex;
	char			*str;
	char			*fstr;
	char			*expand;
	int				idx;
	int				type;
	int				eof;
	int				to_ex;
}	t_parsed;

typedef struct s_shell
{
	t_parsed	*lst;
	t_token		*tlst;
	char		**env;
	char		**arglst;
	char		*str;
}	t_shell;

/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

t_parsed	*info_parsed_list(t_parsed *list);
t_parsed	*type_parsed_list(t_parsed *list);
t_parsed	*p_lstlast(t_parsed *list);
t_token		*last_token(t_token *t);
void		expander(t_shell *s);
void		parser(t_shell *s);
void		token_addlstlast(t_shell *s, t_token *tmp);
void		tokenizer(t_shell *s);
void		print_parsed_list(t_shell *s);
void		ft_charjoin(char **s1, char c, t_shell *s);
void		print_tokens(t_token *list);
void		idx_tokens(t_token *list);
void		print_parsed_tokens(t_token *list);
void		type_tokens(t_token *list);
void		block_tokens(t_token *list);
void		execute_parsed_list(t_shell *s);
void		ft_echo(t_parsed *list);
void		ft_exit(t_parsed *list);
void		sort_var_list(char **dup);
void		ft_print_export_lines(char **dup, int i, int j);
void		free_2d_array(void **ptr);
void		set_q_flag(t_token *list, int *q_flag, char *quotes);
void		free_and_exit(int n, t_shell *shell);
void		plist_strjoin(t_shell *s, int *q_flag, char *quotes);
void		plist_add_to_last(t_parsed **tmp, t_shell *s);
void		plist_add_to_last_ex(t_parsed **tmp, t_shell *s);
void		set_q_flag_ex(t_parsed *list, int *q_flag, char *quotes, int *i);
void		set_sq_flag(int *sq_flag, char c);
void		set_q_flag_plist(t_parsed *list, int *q_flag, char *quotes);
void		remove_quotes(t_shell *s);
void		free_token_list(t_shell *s);
void		free_parsed_list(t_parsed *list);
void		handle_sig1(int sig, siginfo_t *info, void *ucontext);
void		handle_sig2(int sig, siginfo_t *info, void *ucontext);
void		init_signals(struct sigaction sig1, struct sigaction sig2);
void		set_shlvl(t_shell *s);
void		ft_signal(t_shell *s);
char		**dup_envp(char **envp);
char		*token_type(int i);
char		*expand_var(char *str);
char		*get_str(t_parsed *list);
char		*ft_getenv(char *str, t_shell *s);
int			clear_screen(void);
int			error_message(int n, char *exe_name, char *str);
int			ft_pwd(void);
int			ft_setenv(t_shell *s, char *str);
int			is_varname(char *str);
int			ft_chdir(t_shell *s);
int			ft_env(t_shell *s);
int			ft_export(t_shell *s, int env);
int			ft_print_export(char **envp);
int			delimiter_char(char c);
int			op_char(char c);
int			check_is_var(char c);
int			ft_unset(t_shell *s);
#endif
