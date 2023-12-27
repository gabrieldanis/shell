/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/27 14:57:40 by gdanis           ###   ########.fr       */
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
	set_shlvl(s->env);
	//ft_signal(s);
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
			tokenizer(shell);
			//print_tokens(shell->tlst);
			parser(shell);
			print_parsed_list(shell);
			expander(shell);
			/*
			printf("$USER variable: %s", ft_getenv("USER", shell));
			plist = type_parsed_list(plist);
			plist = info_parsed_list(plist);
			execute_parsed_list(shell);
			*/
			free_token_list(shell);
			free_parsed_list(shell->lst);
			shell->lst = NULL;
		}
		if (!shell->str)
			free_and_exit(0, shell);
		free(shell->str);
	}
}
