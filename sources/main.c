/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/23 09:50:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsed	*plist;
	t_token		*list;
	char		**s_envp;
	char		*str;

	s_envp = dup_envp(envp);
	(void) argc;
	(void) argv;
	while (1)
	{
		str = readline("💻 minishell > ");
		if (str[0] != '\0')
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
		free(str);
	}
}
