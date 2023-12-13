/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:15:57 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:16:00 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i])
		i++;
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = f(j, s[j]);
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*
char	ft_toupper(unsigned int i, char ch)
{
	(void) i;
	if (ch >= 'a' && ch <= 'z')
		return (ch - 32);
	else
		return (ch);
}

int	main(void)
{
	char	*start = "what's uP!";
	char	*end;
	char	(*a)(unsigned int, char);

	a = &ft_toupper;

	end = ft_strmapi(start, a);
	printf("original string = %s\n", start);
	printf("after toupper = %s\n", end);
}
*/
