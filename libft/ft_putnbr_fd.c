/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:10:05 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:10:21 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	print_n(unsigned int nb, int fd)
{
	char	number;

	if (nb < 10)
	{
		number = '0' + nb;
		write (fd, &number, 1);
	}
	else
	{
		print_n(nb / 10, fd);
		number = '0' + (nb % 10);
		write (fd, &number, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb_l;

	if (n < 0)
	{
		nb_l = n * -1;
		write(fd, "-", 1);
	}
	else
		nb_l = n;
	print_n(nb_l, fd);
}
/*
int	main(void)
{
	ft_putnbr_fd(0, 1);
}
*/
