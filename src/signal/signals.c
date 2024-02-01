/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:35:19 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/19 20:35:18 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_main.signal_received = TRUE;
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_main.is_cmd_running)
			rl_redisplay();
	}
}

int	signal_set(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
