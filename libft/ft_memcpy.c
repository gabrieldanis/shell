/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:05:32 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:05:37 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && !(dest == NULL && src == NULL))
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char dest [20] = "xxxxxx";
	char *src = "12";
	
	ft_memcpy(dest, src, 4);
	printf("%s\n", dest);
	printf("%s\n", &dest[3]);
}
*/
