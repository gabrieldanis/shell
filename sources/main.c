/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/04 16:24:45 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*s;
	int	loop;

	loop = 1;
	s = init_shell(argc, argv, envp);
	while (loop)
	{
		if (argc >= 2)
		{
			loop = 0;
			s->str = argv[1];
		}
		else
			s->str = readline("💻 minishell > ");
		if (s->str && s->str[0] != '\0')
		{
			if (loop)
				add_history(s->str);
			str_to_token(s);
			if (s->tlst)
			{
				split_token(s);
				expand_token(s);
				//print_token(s);
				init_plst(s);
				parse_lstiter(s, parse_isfile);
				parse_lstiter(s, parse_cmdargs);
				//printlst(s);
				arg_list(s);
				if (s->lst->arglst[0])
					execute_parsed_list(s);
				free_lsts(s);
			}
		}
		if (!s->str)
			free_and_exit(0, s);
		if (loop)
			free(s->str);
		else
		{
			free_2d_array((void **)s->env);
			free(s);
			return (0);
		}
	}
}
