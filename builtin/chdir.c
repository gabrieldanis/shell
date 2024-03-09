/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:17:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/03/09 10:53:52 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	update_pwd(t_shell *s, char *pwd)
{
	char	*tmp;
	char	pwd_new[500];

	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	ft_setenv(s, tmp);
	//free(tmp);
	getcwd(pwd_new, sizeof(pwd_new));
	tmp = ft_strjoin("PWD=", pwd_new);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL, errno);
	ft_setenv(s, tmp);
	//free(tmp);
}

int	ft_chdir(t_shell *s, t_parsed *lst)
{
	char	pwd[500];
	int		n;
	int		i;

	n = 0;
	if (lst->arglst[1])
	{
		if (lst->arglst[2])
		{
			s->rval = 1;
			return (error_message(ARGNUM_ERROR, "cd", NULL, s, errno));
		}
		getcwd(pwd, sizeof(pwd));
		n = chdir(lst->arglst[1]);
		if (n == -1)
			return (error_message(NOCDFILE_ERROR, "cd", lst->arglst[1], s, errno));
		update_pwd(s, pwd);
	}
	else
	{
		i = 0;
		while (s->env[i] && ft_strncmp(s->env[i], "HOME=", 5))
			i++;
		getcwd(pwd, sizeof(pwd));
		n = chdir(ft_strchr(s->env[i], '=') + 1);
		if (n == -1)
		{
			s->rval = 1;
			return (error_message(NOCDFILE_ERROR, "cd",
					ft_strchr(s->env[i], '=') + 1, s, errno));
		}
		update_pwd(s, pwd);
	}
	return (n);
}
