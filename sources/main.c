/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/28 07:11:56 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_var;

void	ft_readline(t_shell *s, char *line, int *gn, int loop_gn)
{
	(void)line;
	(void)gn;
	(void)loop_gn;
	s->str = readline("💻 minishell > ");
	if (!s->str)
		free_and_exit(0, s, NULL, NULL);
}

void	execute_tlst(t_shell *s)
{
	split_token(s);
	expand_token(s);
	init_plst(s);
	parse_lstiter(s, parse_heredoc);
	ft_signal(s);
	parse_lstiter(s, parse_isfile);
	create_outfiles(s);
	parse_lstiter(s, parse_cmdargs);
	count_parsed_nodes(s);
	arg_list(s);
	execute(s);
}

void	execute_line(t_shell *s, int loop, int gn, int *loop_gn)
{
	if (g_var)
		s->rval = 130;
	if (loop && !gn)
		add_history(s->str);
	if (!str_to_token(s))
	{
		if (s->tlst)
		{
			if (!syntax_check(s))
				execute_tlst(s);
			else
				*loop_gn = 0;
			delete_files(s);
			free_lsts(s);
		}
	}
	else
	{
		*loop_gn = 0;
		delete_files(s);
		free_lsts(s);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*s;
	char	*line;
	int		loop;
	int		loop_gn;
	int		gn;

	loop = 1;
	loop_gn = 1;
	gn = 0;
	line = NULL;
	s = init_shell(argc, argv, envp);
	while (loop)
	{
		g_var = 0;
		ft_readline(s, line, &gn, loop_gn);
		if (s->str && s->str[0] != '\0')
			execute_line(s, loop, gn, &loop_gn);
		if (!s->str)
			ft_exit(s, NULL);
		if (loop)
			free_s_str(s);
		s->error = 0;
	}
	free_and_exit(0, s, NULL, NULL);
}
