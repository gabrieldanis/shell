/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:17:30 by gdanis            #+#    #+#             */
/*   Updated: 2023/09/13 16:17:40 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	str_len(char const *s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static int	jump_over_start(char const *s1, char const *set, int i, int j)
{
	int	cntr;
	int	check_cntr;

	i = 0;
	j = 0;
	cntr = 0;
	while (s1[i])
	{
		check_cntr = cntr;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				cntr++;
				i++;
			}
			else
				j++;
		}
		if (cntr == check_cntr)
			return (cntr);
	}
	return (cntr);
}

static int	jump_over_end(char const *s1, char const *set, int i, int j)
{
	int	cntr;
	int	check_cntr;

	i = str_len(s1) - 1;
	j = 0;
	cntr = 0;
	while (i)
	{
		check_cntr = cntr;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				cntr++;
				i--;
			}
			else
				j++;
		}
		if (cntr == check_cntr)
			return (cntr);
	}
	return (cntr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		start;
	int		end;

	j = 0;
	i = 0;
	start = jump_over_start(s1, set, i, j);
	end = 0;
	if (start != str_len(s1))
		end = jump_over_end(s1, set, i, j);
	str = (char *) malloc (sizeof(char) * (str_len(s1) - start - end + 1));
	if (str == NULL)
		return (NULL);
	i = start;
	while (i < (str_len(s1) - end))
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	s1[30] = "21h12311";
	char	*set = "hello";
	printf("%s\n", ft_strtrim(s1, set));
}
*/
