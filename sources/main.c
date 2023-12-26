/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/26 09:49:05 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_parsed	*plist;
	t_token		*list;
	char		**s_envp;
	char		*str;
	struct sigaction	sig1;
	struct sigaction	sig2;

	sig1 = (struct sigaction){0};
	sig2 = (struct sigaction){0};
	s_envp = dup_envp(envp);
	shlvl_plusone(s_envp);
	(void) argc;
	(void) argv;
	init_signals(sig1, sig2);
	str = NULL;
	while (1)
	{
		str = readline("💻 minishell > ");
		if (str && str[0] != '\0')
		{
			add_history(str);
			list = tokenizer(str);
			plist = parser(list);
			plist = expander(plist);
			/*
			print_parsed_list(plist);
			plist = type_parsed_list(plist);
			plist = info_parsed_list(plist);
			*/
			execute_parsed_list(plist, &s_envp, list);
			free_token_list(list);
			free_parsed_list(plist);
		}
		if (!str)
			free_and_exit(0, NULL, NULL, NULL);
		free(str);
	}
}
