/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:17:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/05 10:57:35 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	update_pwd(t_shell *s, char *pwd)
{
	char	*tmp;
	char	pwd_new[500];

	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_setenv(s, tmp);
	getcwd(pwd_new, sizeof(pwd_new));
	tmp = ft_strjoin("PWD=", pwd_new);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_setenv(s, tmp);
}

void	chdir_with_argument(t_shell *s, t_parsed *lst)
{
	char	pwd[500];
	int		n;

	n = 0;
	if (lst->arglst[2])
	{
		s->rval = 1;
		error_message(ARGNUM_ERROR, "cd", NULL, s);
		return ;
	}
	ft_memset(pwd, 0, 500);
	getcwd(pwd, sizeof(pwd));
	if (!pwd[0])
	{
		error_message(NOCDFILE_ERROR, "cd", NULL, s);
		n = chdir(lst->arglst[1]);
		return ;
	}
	n = chdir(lst->arglst[1]);
	if (n == -1)
	{
		error_message(NOCDFILE_ERROR, "cd", lst->arglst[1], s);
		return ;
	}
	else
		s->rval = 0;
	update_pwd(s, pwd);
}

int	chdir_no_argument(t_shell *s)
{
	char	pwd[500];
	int		n;
	int		i;

	i = 0;
	while (s->env[i] && ft_strncmp(s->env[i], "HOME=", 5))
		i++;
	if (!s->env[i])
	{
		error_message(NOHOME_ERROR, "cd", NULL, s);
		return (1);
	}
	getcwd(pwd, sizeof(pwd));
	n = chdir(ft_strchr(s->env[i], '=') + 1);
	if (n == -1)
	{
		s->rval = 1;
		error_message(NOCDFILE_ERROR, "cd", ft_strchr(s->env[i], '=') + 1, s);
		return (1);
	}
	else
		s->rval = 0;
	update_pwd(s, pwd);
	return (0);
}

int	ft_chdir(t_shell *s, t_parsed *lst)
{
	if (lst->arglst[1])
		chdir_with_argument(s, lst);
	else
		chdir_no_argument(s);
	return (0);
}
