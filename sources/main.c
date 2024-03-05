/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/05 16:42:52 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_var;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*s;
	int	loop;
	char *line;

	
	loop = 1;
	s = init_shell(argc, argv, envp);
	while (loop)
	{
		g_var = 0;
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
			line = get_next_line(fileno(stdin));
			//printf("getnextline got this line: %s\n", line);
			if (!line)
			{
				loop = 0;
				free_and_exit(0, s, NULL, NULL);
			}
			s->str = ft_strtrim(line, "\n");
			free(line);
			line = NULL;
		}
		if (s->str && s->str[0] != '\0')
		{
			if (g_var)
				s->rval = g_var;
			if (loop)
				add_history(s->str);
			str_to_token(s);
			if (s->tlst)
			{
				split_token(s);
				print_token(s);
				expand_token(s);
				init_plst(s);
				parse_lstiter(s, parse_heredoc);
				ft_signal(s);
				parse_lstiter(s, parse_isfile);
				parse_lstiter(s, parse_cmdargs);
				count_parsed_nodes(s);
				//printlst(s);
				arg_list(s);
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
