/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:13:51 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/09 12:06:59 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	alpha_smlr(char *i, char *j)
{
	while (*i && *j && *i == *j && *i != '=' && *j != '=')
	{
		i++;
		j++;
	}
	if (*j == '=' || *j < *i)
		return (1);
	else
		return (0);
}

void	sort_var_list(char **dup)
{
	char	*swap;
	int		i;
	int		j;	

	i = 0;
	while (dup[i] && dup[i + 1])
	{
		j = i + 1;
		while (dup[j])
		{
			if (alpha_smlr(dup[i], dup[j]))
			{
				swap = dup[i];
				dup[i] = dup[j];
				dup[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_export_lines(char **dup, int i, int j)
{
	while (dup[i])
	{
		if (ft_strncmp(dup[i], "_=", 2))
		{
			write(1, "declare -x ", 11);
			j = 0;
			while (dup[i][j] && dup[i][j] != '=')
				write(1, &(dup[i][j++]), 1);
			if (dup[i][j] == '=')
			{
				write(1, "=\"", 2);
				j++;
				while (dup[i][j])
				{
					write(1, &(dup[i][j]), 1);
					j++;
				}
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
}

int	is_varname(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '+' && str[i] != '=')
	{
		if (!check_is_var(str[i]))
			return (0);
		i++;
		if (str[i] == '+' && str[i + 1] != '=')
			return (0);
	}
	return (1);
}
