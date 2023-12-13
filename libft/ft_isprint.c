/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:59:54 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 15:59:59 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int x)
{
	if (x >= 32 && x < 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("this is output of ft_isalpha %d \n", ft_isprint(31));
	printf("built in function %d \n", isprint(31));
	printf("this is output of ft_isalpha %d \n", ft_isprint(127));
	printf("built in function %d \n", isprint(127));
}
*/
