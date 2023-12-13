/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:56:57 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 15:57:31 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	ptr = (void *)malloc (nmemb * size);
	i = 0;
	if (ptr)
	{
		while (i < (nmemb * size))
		{
			((char *)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}
/*
int	main(void)
{
	char	*str;

	str = ft_calloc(30, sizeof(char));
	write(1, str, 30);
}
*/
