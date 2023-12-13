/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:48:10 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/13 08:14:09 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/minishell.h"

int	main(void)
{
	char	*str;
	t_token	*list;
	t_parsed	*plist;

	while (1)
	{
		str = readline("💻 minishell > ");
		add_history(str);
		list = tokenizer(str);
		plist = parser(list);
		plist = type_parsed_list(plist);
		plist = info_parsed_list(plist);
		execute_parsed_list(plist);
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
