/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:56:01 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 15:56:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char start [50] = "whaat the fuck is your problem?";
	char start2 [50] = "whaat the fuck is your problem?";

	printf("before my function: %s\n", start);
	ft_bzero(&start[10], sizeof(char)*4);
	printf("after  ft_bzero: %s\n", start);
	printf("after  ft_bzero: %s\n", start + 14);
	bzero(&start2[10], sizeof(char)*4);
	printf("after  bzero: %s\n", start2);
}
*/
