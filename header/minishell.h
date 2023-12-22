/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:49:31 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/22 15:56:07 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*********************************
 * 	INCLUDES
 *********************************/


# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"


/*********************************
 * 	ERROR CODES
 *********************************/


# define MALLOC_ERROR 1
# define QUOTE_ERROR 2
# define IDENT_ERROR 3
# define GEN_ERROR 4
# define NOFILE_ERROR 5


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
	struct s_parsed *ex;
	char			*str;
	char			*expand;
	int			idx;
	int			type;
	int			eof;
	int			to_ex;
}	t_parsed;



/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/


t_parsed	*parser(t_token *list);
t_parsed	*info_parsed_list(t_parsed *list);
t_parsed	*type_parsed_list(t_parsed *list);
t_parsed	*p_lstlast(t_parsed *list);
t_parsed	*expander(t_parsed *plist);
t_token		*tokenizer(char *str);
t_token		*last_token(t_token *t);
void		print_parsed_list(t_parsed *list);
void		ft_charjoin(char **s1, char c);
void		print_tokens(t_token *list);
void		idx_tokens(t_token *list);
void		print_parsed_tokens(t_token *list);
void		type_tokens(t_token *list);
void		block_tokens(t_token *list);
void		execute_parsed_list(t_parsed *plist, char ***envp, t_token *list);
void		ft_echo(t_parsed *list);
void		ft_exit(t_parsed *list);
void		sort_var_list(char **dup);
void		ft_print_export_lines(char **dup, int i, int j);
void		free_2d_array(void **ptr);
void		set_q_flag(t_token *list, int *q_flag, char *quotes);
void		free_and_exit(int n, t_token *list, t_parsed *plist, char **envp);
void		plist_strjoin(t_parsed *plist, t_token **list, int *q_flag, char *quotes);
void		plist_add_to_last(t_parsed **tmp, t_parsed **plist);
void		plist_add_to_last_ex(t_parsed **tmp, t_parsed **plist);
void		set_q_flag_ex(t_parsed *list, int *q_flag, char *quotes, int *i);
void		set_sq_flag(int *sq_flag, char c);
void		set_q_flag_plist(t_parsed *list, int *q_flag, char *quotes);
void		remove_quotes(t_parsed *plist);
void		free_token_list(t_token *list);
void		free_parsed_list(t_parsed *list);
int		clear_screen(void);
char		**dup_envp(char **envp);
char		*token_type(int i);
char		*expand_var(char *str);
char		*get_str(t_parsed *list);
int		error_message(int n, char *exe_name, char *str);
int		ft_pwd(void);
int		ft_setenv(char ***envp, char *str);
int		is_varname(char *str);
int		ft_chdir(t_parsed *list, char ***envp);
int		ft_env(char **envp);
int		ft_export(char ***envp, t_parsed *list, int env);
int		ft_print_export(char **envp);
int		delimiter_char(char c);
int		op_char(char c);
int		check_is_var(char c);
int		ft_unset(char ***envp, t_parsed *list);
#endif
