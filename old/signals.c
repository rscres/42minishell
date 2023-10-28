/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:52:48 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 13:03:26 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
		readline("my_shell$ ");
	else if (signo == SIGQUIT)
		return ;
	else if (signo == SIGTSTP)
	{
		printf("here\n");
		ft_putstr_fd("Quit: 3\n", 1);
		exit(1);
	}
	else
		ft_putstr_fd("Signal not handled\n", 1);
}

void	sig_init(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr("can't catch SIGINT\n");
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putstr("can't catch SIGQUIT\n");
	if (signal(SIGTSTP, sig_handler) == SIG_ERR)
		ft_putstr("can't catch SIGTSTP\n");
}
