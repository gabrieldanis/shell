/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:17:56 by gdanis            #+#    #+#             */
/*   Updated: 2023/12/21 19:38:44 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	update_pwd(char ***envp, char *pwd)
{
	char	*tmp;
	char	pwd_new[500];

	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	ft_setenv(envp, tmp);
	free(tmp);
	getcwd(pwd_new, sizeof(pwd_new));
	tmp = ft_strjoin("PWD=", pwd_new);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, NULL, NULL, NULL);
	ft_setenv(envp, tmp);
	free(tmp);
}

int	ft_chdir(t_parsed *list, char ***envp)
{
	int	n;
	char	pwd[500];
	int	i;

	// add && list->next->type == ??? after parsing
	if (list->next)
	{
		getcwd(pwd, sizeof(pwd));
		n = chdir(get_str(list->next));
		if (n == -1)
			return(error_message(NOFILE_ERROR, "cd", get_str(list->next)));
		update_pwd(envp, pwd);
	}
	else
	{
		i = 0;	
		while ((*envp)[i] && ft_strncmp((*envp)[i], "HOME=", 5))
			i++;
		getcwd(pwd, sizeof(pwd));
		n = chdir(ft_strchr((*envp)[i], '=') + 1);
		if (n == -1)
			return(error_message(NOFILE_ERROR, "cd", ft_strchr((*envp)[i], '=') + 1));
		update_pwd(envp, pwd);
	}
	return (n);
}
