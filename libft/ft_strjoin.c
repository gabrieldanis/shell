/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:08 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/11 15:42:06 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_size(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
	{
		i++;
		j++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char					*str;
	unsigned int			i;
	unsigned int			j;

	i = 0;
	j = 0;
	str = (char *) malloc ((sizeof(char)) * (ft_size(s1, s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i] = ((char *)s2)[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main(void)
{
	char *str1 = "123";
	char *str2 = "4567";
	char *result;
	int i = 0;

	result = ft_strjoin(str1, str2);
	while (result[i] != '\0')
		{
			write(1, &result[i], 1);
			i++;
		}
		write (1, "\n", 1);
		free (result);

}
*/	
