/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:15:31 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/14 10:34:28 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	else
		return (0);
}
/*
int	main(void)
{
	printf("my code = %lu \n", ft_strlen(" "));
	printf("built in code = %lu \n", strlen(" "));
}
*/
