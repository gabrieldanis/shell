/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:58:41 by gdanis            #+#    #+#             */
/*   Updated: 2023/10/14 19:13:07 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int x)
{
	if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("my function %d \n", ft_isalpha('t'));
	printf("built in function %d \n", isalpha('t'));
	printf("my function %d \n", ft_isalpha(128));
	printf("built in function %d \n", isalpha(128));
}
*/
