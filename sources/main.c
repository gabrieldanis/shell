/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/08 11:41:56 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_var;

void	ft_readline(t_shell *s, char *line, int *gn, int loop_gn)
{
	signal_handler(0);
	(void)line;
	(void)gn;
	(void)loop_gn;
	s->str = readline("💻 minishell > ");
	if (!s->str)
	{
		printf("exit\n");
		free_and_exit(0, s, NULL, NULL);
	}
	signal_handler(1);
}

void	execute_tlst(t_shell *s)
{
	split_token(s);
	expand_token(s);
	init_plst(s);
	if (parse_lstiter(s, parse_heredoc))
	{
		ft_signal(s);
		return ;
	}
	ft_signal(s);
	parse_lstiter(s, parse_isfile);
	parse_lstiter(s, parse_cmdargs);
	count_parsed_nodes(s);
	if (s->cmds == 1)
		create_outfiles(s);
	if (!s->outfile_error)
	{
		arg_list(s);
		execute(s);
	}
	s->outfile_error = 0;
}

void	execute_line(t_shell *s, int loop, int gn, int *loop_gn)
{
	if (g_var)
	{
		s->rval = 130;
		g_var = 0;
	}
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
