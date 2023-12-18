/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:49:31 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/17 08:50:07 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*********************************
 * 	INCLUDES
 *********************************/


#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"




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
	char			*str;
	char			*expand;
	int			idx;
	int			type;
	int			eof;
}	t_parsed;



/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/


t_parsed	*parser(t_token *list);
t_parsed	*info_parsed_list(t_parsed *list);
t_parsed	*type_parsed_list(t_parsed *list);
t_token		*tokenizer(char *str);
t_token		*last_token(t_token *t);
void		print_parsed_list(t_parsed *list);
void		ft_charjoin(char **s1, char c);
void		print_tokens(t_token *list);
void		idx_tokens(t_token *list);
void		print_parsed_tokens(t_token *list);
void		type_tokens(t_token *list);
void		block_tokens(t_token *list);
void		execute_parsed_list(t_parsed *list, char **envp);
void		ft_echo(t_parsed *list);
void		ft_exit(t_parsed *list);
void		ft_pwd(void);
void		ft_setenv(char ***envp, char *str);
void		sort_var_list(char **dup);
void		ft_print_export_lines(char **dup, int i, int j);
void		free_2d_array(void **ptr);
char		**dup_envp(char **envp);
char		*token_type(int i);
char		*expand_var(char *str);
int		ft_chdir(t_parsed *list);
int		ft_env(char **envp);
int		ft_export(char **envp, t_parsed *list, int env);
int		ft_print_export(char **envp);
#endif
