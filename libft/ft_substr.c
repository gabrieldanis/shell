/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:17:53 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:46:35 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*fill_mem(char const *s, int start, unsigned int size, char *substr)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		substr[i] = ((char *)s)[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substr;
	unsigned int		i;
	unsigned int		j;
	unsigned int		size;

	i = 0;
	j = 0;
	while (s[j])
		j++;
	if (j <= start)
		size = 0;
	else
	{
		while (i < len && s[start + i])
			i++;
		size = i;
	}
	substr = (char *) malloc (sizeof(char) * (size + 1));
	if (substr == NULL)
		return (NULL);
	return (fill_mem(s, start, size, substr));
}
/*
int	main(void)
{
	char	str [30] = "abcde";
	unsigned int	start	= 1;
	size_t	len = 3;
	char	*substr;
	int i = 0;

	substr = ft_substr(str, start, len);
	if (substr == NULL)
	{
		printf("error");
		return(0);
	}
	while (substr[i] != '\0')
	{
		write(1, &substr[i], 1);
		i++;
	}
	write (1, "\n", 1);
	free (substr);
}
*/
