/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:59:04 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 15:59:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int x)
{
	if (x >= 0 && x <= 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("my function %d \n", ft_isascii('a'));
	printf("built in function %d \n", isascii('a'));
	printf("my function %d \n", ft_isascii(128));
	printf("built in function %d \n", isascii(128));
}
*/
