/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:11:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:12:00 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	else
		return (NULL);
}
/*
int	main(void)
{
	char	*str = "ha\0df";
	int	x = 0;

	printf("my function = %s, index number = %ld\n", 
	ft_strchr(str, x), ft_strchr(str, x) - str);
	printf("my function = %s, index number = %ld\n", 
	strchr(str, x), strchr(str, x) - str);
}
*/
