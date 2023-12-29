/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/29 19:05:35 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_signal = 0;

t_shell	*init_shell(char **envp)
{
	t_shell	*s;

	s = (t_shell *)malloc(sizeof(t_shell));
	if (!s)
	{
		error_message(MALLOC_ERROR, NULL, NULL);
		exit(0);
	}
	*s = (t_shell){0};
	s->env = dup_envp(envp);
	set_shlvl(s);
	//update shell name here
	ft_signal(s);
	s->str = NULL;
	return (s);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	while (1)
	{
		shell->str = readline("💻 minishell > ");
		if (shell->str && shell->str[0] != '\0')
		{
			add_history(shell->str);
			//tokenizer(shell);
			str_to_token(shell);
			split_token(shell);
			expand_token(shell);
			print_tokens(shell);
			//parser(shell);
			//expander(shell);
			//print_parsed_list(shell);
			//execute_parsed_list(shell);
			/*
			printf("$USER variable: %s", ft_getenv("USER", shell));
			plist = type_parsed_list(plist);
			plist = info_parsed_list(plist);
			*/
			free_token_list(shell);
			//free_parsed_list(shell->lst);
			shell->lst = NULL;
			if (shell->arglst)
				free_2d_array((void **)shell->arglst);
			shell->arglst = NULL;
		}
		if (!shell->str)
			free_and_exit(0, shell);
		free(shell->str);
	}
}
