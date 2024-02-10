/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:15:09 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:15:12 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			i;
	int				j;

	j = 0;
	while (src[j])
		j++;
	if (size == 0)
		return (j);
	i = 0;
	while (i < size - 1 && src[i])
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (j);
}

/*
int	main(void)
{
	char	*src = "123";
	char	dest [4] = "abc";
	int	result;

	result = ft_strlcpy(dest, src, 0);
	printf("%s\n", dest);
	printf("%d\n", result);
}
*/
