/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:45:34 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/16 17:22:42 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_n_flag(char *arg)
{
	int	i;

	i = 1;
	while (arg && arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_flag_before(char **arg)
{
	while (*arg && check_n_flag(*arg))
		arg++;
	if (arg)
		return (FALSE);
	return (TRUE);
}

static int	handle_n_flag(char *arg, int *n_flag, int flag_before, int *i)
{
	if (arg[0] == '-' && check_n_flag(arg) && ft_strlen(arg) > 1 && flag_before)
	{
		*n_flag = TRUE;
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	n_flag;
	int	flag_before;

	i = 0;
	n_flag = FALSE;
	flag_before = TRUE;
	while (args[i] && args)
	{
		if (handle_n_flag(args[i], &n_flag, flag_before, &i))
			continue ;
		if (args[i] != NULL && ft_strcmp(args[i], ""))
			ft_putstr_fd(args[i], fd);
		flag_before = is_flag_before(args);
		if (args[i + 1] != NULL && ft_strcmp(args[i], ""))
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
