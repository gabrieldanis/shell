/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:35 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:16:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (big[i + j] == little[j])
		{
			j++;
			if (i + j > len)
				return (NULL);
			if (little[j] == '\0')
			{
				return ((char *)(&big[i]));
			}
		}
		j = 0;
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*haystack;
	char	*needle;

	haystack = "asggmbs";
	needle = "ggm";
	printf("%s\n", ft_strnstr(haystack, needle, 6));
	printf("%s\n", strnstr(haystack, needle, 6));
}
*/
