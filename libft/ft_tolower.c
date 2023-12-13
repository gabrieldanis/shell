/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:18:22 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:18:25 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int a)
{
	if (a >= 'A' && a <= 'Z')
		return (a + 32);
	else
		return (a);
}
/*
int	main(void)
{
	int	a = 65;

	printf("integer as input no small letter: %c \n", a);
	printf("integer as input no small letter: %c \n", ft_tolower(a));
	printf("integer as input no small letter: %c \n", tolower(a));
}
*/
