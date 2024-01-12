/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:45:34 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/23 20:42:34 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_n_flag(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && check_n_flag(args[i]))
		{
			printf("n_flag\n");
			n_flag = 1;
			i++;
			continue ;
		}
		if (args[i] != NULL && ft_strcmp(args[i], ""))
			ft_putstr_fd(args[i], fd);
		if (args[i + 1] != NULL && ft_strcmp(args[i], ""))
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
