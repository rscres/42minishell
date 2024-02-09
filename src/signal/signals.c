/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:35:19 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/09 13:54:59 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigquit(int sig)
{
	(void)sig;
	if (g_main.is_cmd_running)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_main.status = 131;
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_main.status = 130;
	}
}

void	sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_main.signal_received = TRUE;
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_main.is_cmd_running)
			rl_redisplay();
		g_main.status = 130;
	}
}

int	signal_set(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
