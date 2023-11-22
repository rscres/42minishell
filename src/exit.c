/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:46:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/22 00:19:17 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//needs rework
void	ft_exit(char **args, int argc)
{
	int		i;
	int		status;
	// char	*value;

	clear_hashtable(g_main.env_var);
	clear_token_list();
	printf("exit\n");
	if (!args[0])
	{
		clear_cmd_list();
		exit(0);
	}
	i = 0;
	// if (ft_strcmp(args[0], "+") || ft_strcmp(args[0], "-"))
	// {
	// 	i++;
	// 	value = ft_strjoin(args[0], args[1]);
	// 	clear_cmd_list();
	// 	exit(ft_atoi(value));
	// }
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]) && args[0][i] != '-' && args[0][i] != '+')
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clear_cmd_list();
			exit(2);
		}
		i++;
	}
	status = 0;
	status = ft_atoi(args[0]);
	while (status > 255)
		status -= 256;
	while (status > 0)
		status += 256;
	if (argc > 1)
	{	
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		clear_cmd_list();
		exit(1);
	}
	clear_cmd_list();
	exit(status);
}

void	ft_exit2(int status)
{
	clear_hashtable(g_main.env_var);
	clear_cmd_list();
	clear_token_list();
	printf("exit\n");
	while (status > 255)
		status -= 256;
	exit(status);
}