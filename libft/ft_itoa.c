/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:00:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:02:46 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	rev(char *str)
{
	int	i;
	int	size;
	int	temp;

	size = 0;
	while (str[size])
		size++;
	i = 0;
	while (i < size / 2)
	{
		temp = str [i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = temp;
		i++;
	}
}

static int	mem_size(int nbr)
{
	int		nb_slots;
	int		n;

	n = nbr;
	nb_slots = 1;
	if (n < 0)
		nb_slots++;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		nb_slots++;
	}
	return (nb_slots);
}

static void	fill_mem(char *str, unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		str[i] = ('0' + (n % 10));
		n = n / 10;
		i++;
	}
	str[i] = '0' + n;
	str[i + 1] = '\0';
	rev(str);
}

char	*ft_itoa(int n)
{
	unsigned int	nb_l;
	char			*str;
	int				i;

	str = (char *) malloc ((1 + mem_size(n)) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		nb_l = (-1) * n;
		str[i] = '-';
		i++;
	}
	else
		nb_l = n;
	fill_mem(&str[i], nb_l);
	return (str);
}
/*
int	main(void)
{
	char	*result;
	result = ft_itoa(-1234);
	printf("%s\n", result);
	free(result);

}
*/
