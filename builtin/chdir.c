/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <gdanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:17:56 by gdanis            #+#    #+#             */
/*   Updated: 2024/04/07 20:06:01 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	update_pwd(t_shell *s, char *str)
{
	char	*tmp;
	char	pwd_new[500];

	tmp = ft_strjoin("OLDPWD=", s->cwd);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_setenv(s, tmp);
	ft_memset(pwd_new, 0, 500);
	getcwd(pwd_new, sizeof(pwd_new));
	if (!pwd_new[0])
		tmp = create_broken_pwd(s, str);
	else
		tmp = ft_strjoin("PWD=", pwd_new);
	if (!tmp)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
	ft_setenv(s, tmp);
	if (s->cwd)
		free (s->cwd);
	s->cwd = NULL;
	s->cwd = ft_strdup(tmp + 4);
	if (!s->cwd)
		free_and_exit(MALLOC_ERROR, s, NULL, NULL);
}

void	check_cwd(t_shell *s)
{
	char	pwd[500];

	ft_memset(pwd, 0, 500);
	getcwd(pwd, sizeof(pwd));
	if (!pwd[0])
		error_message(NOCDFILE_ERROR, "cd", NULL, s);
	s->rval = 0;
}

void	chdir_with_argument(t_shell *s, t_parsed *lst)
{
	int		n;

	n = 0;
	if (lst->arglst[2])
	{
		s->rval = 1;
		error_message(ARGNUM_ERROR, "cd", NULL, s);
		return ;
	}
	if (lst->arglst[1][0] == '-')
	{
		errno = 2;
		error_message(IDENT_ERROR, "cd", lst->arglst[1], s);
		return ;
	}
	n = chdir(lst->arglst[1]);
	if (n == -1)
	{
		error_message(NOCDFILE_ERROR, "cd", lst->arglst[1], s);
		return ;
	}
	else
		check_cwd(s);
	update_pwd(s, lst->arglst[1]);
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
