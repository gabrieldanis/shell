/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:18:38 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:18:42 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int a)
{
	if (a >= 'a' && a <= 'z')
		return (a - 32);
	else
		return (a);
}
/*
int	main(void)
{
	int	a = 97;
	char	b = 'z';
	int	c = 122;

	printf("integer as input no small letter: %c \n", ft_toupper(a));
	printf("integer as input no small letter: %c \n", toupper(a));
	printf("integer as input small char: %c \n", ft_toupper(b));
	printf("integer as input small char: %c \n", toupper(b));
	printf("integer as input small char: %c \n", ft_toupper(c));
	printf("integer as input small char: %c \n", toupper(c));
}
*/
