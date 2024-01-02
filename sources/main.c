/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 16:16:33 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	shell = init_shell(argc, argv, envp);
	while (1)
	{
		shell->str = readline("💻 minishell > ");
		if (shell->str && shell->str[0] != '\0')
		{
			add_history(shell->str);
			str_to_token(shell);
			if (shell->tlst)
			{
				split_token(shell);
				expand_token(shell);
				//print_token(shell);
				init_plst(shell);
				parse_lstiter(shell, parse_isfile);
				parse_lstiter(shell, parse_cmdargs);
				//printlst(shell);
				arg_list(shell);
				execute_parsed_list(shell);
				free_lsts(shell);
			}
		}
		if (!shell->str)
			free_and_exit(0, shell);
		free(shell->str);
	}
}
