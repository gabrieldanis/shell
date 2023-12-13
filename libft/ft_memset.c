/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:07:47 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:07:48 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char start [50] = "whaat the fuck is your problem?";
	char start2 [50] = "whaat the fuck is your problem?";

	printf("before my function: %s\n", start);
	printf("return value ft_memset: %s\n", 
	(char *)ft_memset(&start[10], '*', sizeof(char)*4));
	printf("after  ft_memset: %s\n", start);
	memset(&start2[10], '*', sizeof(char)*4);
	printf("after  memset: %s\n", start2);
}
*/
