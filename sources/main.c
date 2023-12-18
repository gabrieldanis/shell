/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/18 16:02:52 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*list;
	t_parsed	*plist;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		str = readline("💻 minishell > ");
		add_history(str);
		list = tokenizer(str);
		print_tokens(list);
		plist = parser(list);
		print_parsed_list(plist);
		/*
		plist = type_parsed_list(plist);
		plist = info_parsed_list(plist);
		execute_parsed_list(plist, envp);
		*/
		if (!ft_strncmp(str, "exit", 4))
		{
			if (str[4] == '\0' || str[4] == ' ' || str[4] == '\t')
			{
				free(str);
				exit(0);
			}
		}
		free(str);
	}
}
