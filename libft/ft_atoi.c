/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:55:00 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 07:57:32 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	number;
	int	minus;

	minus = 1;
	number = 0;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = minus * (-1);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10;
		number = number + (*nptr - '0');
		nptr++;
	}
	return (number * minus);
}
/*
int main(void)
{
	char mystr[] = "";

	printf("%d\n", ft_atoi(mystr));
	printf("%d\n", atoi(mystr));
}
*/
