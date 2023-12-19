/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 08:49:36 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/19 14:40:28 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_2d_array(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	delimiter_char(char c)
{
	if (c == ' ' || c == '\0' || c == '|' || c == '<' 
		|| c == '>')
		return (1);
	return (0);
}

int	op_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
