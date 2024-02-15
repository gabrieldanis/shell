/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/02/11 14:56:19 by dberes           ###   ########.fr       */
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
		/*
		if (argc >= 2)
		{
			loop = 0;
			s->str = argv[1];
		}
		*/
		if((isatty(fileno(stdin))))
		{
			s->str = readline("💻 minishell > ");
			if (!s->str)
				free_and_exit(0, s, NULL, NULL);
		}
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			s->str = ft_strtrim(line, "\n");
			free(line);
		}

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
				parse_lstiter(s, parse_heredoc);
				parse_lstiter(s, parse_isfile);
				parse_lstiter(s, parse_cmdargs);
				count_parsed_nodes(s);
				//printlst(s);
				arg_list(s);
				if (s->lst->arglst && s->lst->arglst[0])
					execute(s);
				delete_files(s);
				free_lsts(s);
				
			}
		}
		if (!s->str)
			ft_exit(s, NULL);
		if (loop)
			free(s->str);
	}
	free_and_exit(0, s, NULL, NULL);
}
