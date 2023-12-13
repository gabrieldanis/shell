/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:12:15 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:12:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		l;
	int		i;
	char	*dest;

	l = 0;
	while (s[l])
		l++;
	dest = (char *) malloc (l + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = ((char *)s)[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	source[] = "123";
	char	*destination;

	destination = ft_strdup(source);

	printf("This is the string that needs to be duplicated: %s\n", source);	
	printf("This is the duplicated one: %s\n", destination);	
	free(destination);
}
*/
