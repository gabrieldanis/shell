/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:37:12 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/18 09:38:31 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	shlvl_one(t_shell *s, char *tmp, int checker)
{
	if (!checker)
	{
		tmp = ft_strdup("SHLVL=1");
		if (!tmp)
			free_and_exit(MALLOC_ERROR, s, NULL, NULL);
		ft_setenv(s, tmp);
	}
}

void	ft_getcwd(t_shell *s, char **path_var)
{
	char	path[500];

	if (getcwd(path, sizeof(path)) == NULL)
		free_and_exit(GEN_ERROR, s, NULL, NULL);
	*path_var = ft_strjoin("PWD=", path);
	if (!(*path_var))
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
}

void	malloc_dup(t_shell *s, char ***dup, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	*dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*dup))
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
}
