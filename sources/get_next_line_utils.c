/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:13:16 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/20 13:13:19 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*set_zero(char *str, size_t rread, int *i, char **nullme)
{
	int	j;

	if (rread != 0)
	{
		if (rread == (size_t)(*i))
			*i = 0;
		return (NULL);
	}
	if (i)
		*i = 0;
	j = 0;
	if (str)
	{
		while (j < BUFFER_SIZE)
		{
			str[j] = '\0';
			j++;
		}
		return (str);
	}
	if (nullme)
		*nullme = NULL;
	return (NULL);
}

char	*malloc_size_i(int i)
{
	char	*str;

	if (i != 0)
	{
		str = (char *) malloc (i + 1);
		if (!str)
			return (NULL);
		return (str);
	}
	return (NULL);
}

int	len(char *str, int rread, int i, int checker)
{
	int	j;

	j = 0;
	if (checker == 1)
	{
		while (i + j < rread && str[i + j] != '\n')
			j++;
		if ((i + j) != rread)
		{
			if (str[i + j] == '\n')
				j++;
		}
		return (j);
	}
	else
	{
		if (str)
		{
			while (str[j])
				j++;
		}
		return (j);
	}
}

int	check_str_nl(char *str, unsigned long rread)
{
	unsigned long	j;

	j = 0;
	if (rread == 0)
	{
		while (str[j])
		{
			if (str[j] == '\n')
				return (1);
			j++;
		}
		return (0);
	}
	while (j < rread && str[j])
	{
		if (str[j] == '\n')
			return (1);
		j++;
	}
	return (0);
}

char	*conc(char *mem, char *str, int *i, int len)
{
	char	*concat_str;
	int		j;
	int		k;

	concat_str = malloc_size_i(len);
	if (!concat_str)
		return (free(mem), NULL);
	j = 0;
	if (mem != NULL)
	{
		while (mem[j])
		{
			concat_str[j] = mem[j];
			j++;
		}
	}
	k = 0;
	while (j + k < len)
	{
		concat_str[j + k] = str[*i];
		k++;
		(*i)++;
	}
	concat_str[j + k] = '\0';
	return (free(mem), concat_str);
}
