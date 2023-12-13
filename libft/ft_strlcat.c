/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:33 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:13:47 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	size_dst;
	size_t	size_src;

	size_dst = 0;
	size_src = 0;
	while (dst[size_dst])
		size_dst++;
	while (src[size_src])
		size_src++;
	if (size == 0 || size_dst > size)
		return (size_src + size);
	i = 0;
	j = size_dst;
	while ((size_dst + i) < size - 1 && src[i])
	{
		*(dst + j) = *(src + i);
		i++;
		j++;
	}
	*(dst + j) = '\0';
	return (size_dst + size_src);
}
/*
int	main(void)
{
	char	*src1 = "12345678";
	char	dest1 [5] = "abc";
	int	result1;
	char	*src2 = "12345678";
	char	dest2 [5] = "abc";
	int	result2;

	result1 = ft_strlcat(dest1, src1, 0);
	printf("my function %s\n", dest1);
	printf("%d\n", result1);

	result2 = strlcat(dest2, src2, 0);
	printf("original function %s\n", dest2);
	printf("%d\n", result2);
}
*/
