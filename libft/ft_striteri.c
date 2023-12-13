/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:12:34 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:12:39 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}
/*
void	ft_toupper(unsigned int i, char *ch)
{
	(void) i;

	if (*ch >= 'a' && *ch <= 'z')
		*ch = *ch - 32;
}

int	main(void)
{
	char	start [50] = "what's uP!";
	void	(*a)(unsigned int, char *);

	a = NULL;

	printf("original string = %s\n", start);
	ft_striteri(start, a);
	printf("after toupper = %s\n", start);
}
*/
