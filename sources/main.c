/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/15 10:13:25 by gdanis           ###   ########.fr       */
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
	while (1)
	{
		str = readline("💻 minishell > ");
		add_history(str);
		list = tokenizer(str);
		plist = parser(list);
		plist = type_parsed_list(plist);
		plist = info_parsed_list(plist);
		execute_parsed_list(plist, envp);
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
