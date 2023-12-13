/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:57:55 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 15:58:06 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(unsigned char x)
{
	if ((x >= '0' && x <= '9') || (x >= 'A' && x <= 'Z')
		|| (x >= 'a' && x <= 'z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("this is output of ft_isalpha %d \n", ft_isdigit(245));
	printf("built in function %d \n", isdigit(245));
}
*/
