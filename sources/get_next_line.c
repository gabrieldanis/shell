/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:13:27 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 13:22:24 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE];
	static int	i;
	static int	rread;
	static char	*mem;

	set_zero(NULL, 0, NULL, &mem);
	while (1)
	{
		if (!i)
		{
			rread = read(fd, str, BUFFER_SIZE);
			if (rread == -1)
				return (free(mem), NULL);
			if (rread == 0)
				return (set_zero(str, 0, &i, NULL), mem);
		}
		mem = conc(mem, str, &i, len(str, rread, i, 1) + len(mem, 0, 0, 0));
		if (!mem)
			return (NULL);
		if (check_str_nl(mem, len(mem, 0, 0, 0)))
			return (set_zero(NULL, rread, &i, NULL), mem);
		if (i == rread)
			set_zero(str, 0, &i, NULL);
	}
}
