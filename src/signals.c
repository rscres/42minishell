/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:35:19 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/11 19:31:00 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		// rl_reset_line_state();
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_main.is_heredoc_running)
			rl_redisplay();
	}
}

int	signal_set(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
