/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:35:19 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/01 13:24:56 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	signal_set(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
