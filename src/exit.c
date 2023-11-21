/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:46:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/21 01:50:00 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_exit(char **args, int argc)
{
	clear_hashtable(g_main.env_var);
	clear_cmd_list();
	clear_token_list();
	printf("exit\n");
	while (status > 255)
		status -= 256;
	if (argc > 1)
	{	
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		exit(1);
	}
	exit(status);
}