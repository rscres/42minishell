/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:46:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/29 15:22:45 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	adjust_status(int status)
{
	while (status > 255)
		status -= 256;
	while (status < 0)
		status += 256;
	return (status);
}

static void	check_if_num(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clear_cmd_list();
			exit(2);
		}
		i++;
	}
}

//needs rework
void	ft_exit(char **args, int argc)
{
	int		status;

	clear_hashtable(g_main.env_var);
	clear_token_list();
	printf("exit\n");
	if (argc > 2)
	{	
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		clear_cmd_list();
		exit(1);
	}
	if (args && args[1] == NULL)
	{
		clear_cmd_list();
		exit(g_main.status);
	}
	check_if_num(args[1]);
	status = adjust_status(ft_atoi(args[1]));
	clear_cmd_list();
	exit(status);
}

void	ft_exit2(int status)
{
	clear_hashtable(g_main.env_var);
	clear_cmd_list();
	clear_token_list();
	printf("exit\n");
	exit(adjust_status(status));
}
