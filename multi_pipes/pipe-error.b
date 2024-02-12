/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdanis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:07:17 by gdanis            #+#    #+#             */
/*   Updated: 2024/01/15 18:07:48 by gdanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	path_error(t_data *data)
{
	int		i;
	char	**args;

	i = 2;
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		ft_printf("pipex: %s: command not found\n", args[0]);
		free_array(args);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	check_args(t_data *data, int *ex)
{
	int		i;
	char	**args;

	i = 2;
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		if (!args)
			free_exit(args, data, NULL, 4);
		if (args[0] == NULL)
		{
			ft_printf("pipex: : command not found\n");
			*ex = 1;
		}
		free_array(args);
		i++;
	}
}

void	check_commands_bonus(t_data *data, int *ex)
{
	int		i;
	char	**args;

	i = 2;
	data->fd_inf = open(data->argv[1], O_RDONLY);
	if (data->fd_inf == -1)
	{
		print_fd_error(data);
		*ex = 1;
	}
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		if (!args)
			free_exit(args, data, NULL, 4);
		if (args[0] != NULL)
			dir_copy(args, data, ex, i);
		free_array(args);
		i++;
	}
	if (*ex == 1)
	{
		free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
}
