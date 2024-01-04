/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:25:50 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/02 11:26:10 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
