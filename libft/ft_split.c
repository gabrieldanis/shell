/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:47:23 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/17 08:48:50 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	jmp(char *str, char c, int i, int word)
{
	int	start;

	start = i;
	if (word == 1)
	{
		while (str[i])
		{
			if (str[i] == c)
				return (i - start);
			i++;
		}
	}
	if (word == 0)
	{
		while (str[i] == c)
			i++;
	}
	return (i - start);
}

static int	w_c(char *str, char c)
{
	int	words;
	int	k;
	int	temp;

	words = 0;
	k = 0;
	while (str[k])
	{
		k += jmp(str, c, k, 0);
		temp = k;
		k += jmp(str, c, k, 1);
		if (k != temp)
			words++;
	}
	return (words);
}

static char	*str_copy(char *str, char *dest, char c, int i)
{
	int	j;
	int	len;

	j = 0;
	len = jmp(str, c, i, 1);
	while (j < len)
	{
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static void	free_everything(char **o, int j)
{
	while (j > 0)
	{
		j--;
		free(o[j]);
	}
	free (o);
}

char	**ft_split(char const *s, char c)
{
	char	**o;
	char	*pntr;
	int		i;
	int		j;

	o = (char **) malloc ((w_c((char *)s, c) + 1) * sizeof(char *));
	if (o == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (j < w_c((char *)s, c))
	{
		i += jmp((char *)s, c, i, 0);
		pntr = (char *) malloc (sizeof(char) * (1 + jmp((char *)s, c, i, 1)));
		if (pntr == NULL)
		{
			free_everything(o, j);
			return (NULL);
		}
		o[j++] = str_copy((char *)s, pntr, c, i);
		i += jmp((char *)s, c, i, 1);
	}
	o[j] = NULL;
	return (o);
}
/*
int     main(void)
{
        char *mystr = ",,hello,there,,,,whats,up,";
        char seperator = ',';
        char **lines;
        int     i;

        i = 0;
        lines = ft_split(mystr, seperator);
        while(i <= w_c(mystr, seperator))
        {
                printf("%d: %s\n", (i+1), lines[i]);
                i++;
        }
}
*/
