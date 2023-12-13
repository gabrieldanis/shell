/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:06:15 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:07:16 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		while (n)
		{
			*(unsigned char *)(dest + n - 1) = *(unsigned char *)(src + n - 1);
			n--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	int src [20] = {1,2,3,4,5,6};
	int *dest = &src[2];
	int i;
	int *temp;
	
	temp = (int *)(memmove(dest, src, sizeof(int)*2));
	i = 0;
	while (i < 4)
	{
		printf("%d\n", temp[i]);
		i++;
	}
}
*/
