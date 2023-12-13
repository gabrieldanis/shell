/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:17:08 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:17:11 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*sol;

	sol = (char *) s;
	i = 0;
	while (sol[i])
		i++;
	while (i >= 0)
	{
		if (sol[i] == (char)c)
			return (&sol[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*str = "shasdfs";
	char	x = '\0';

	printf("my function = %s, index number = %ld\n", 
	ft_strrchr(str, x), ft_strrchr(str, x) - str);
	printf("lib function = %s, index number = %ld\n", 
	strrchr(str, x), strrchr(str, x) - str);
}
*/
