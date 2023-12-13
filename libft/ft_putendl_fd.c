/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:09:35 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:09:42 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, s + i, 1);
		i++;
	}
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	char	*str = "Hello there.";

	ft_putendl_fd(str, 1);
}
*/
