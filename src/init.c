/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:06:47 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/27 13:42:58 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_hashtable(t_env **env_var)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
		env_var[i++] = NULL;
}

void	init_global(void)
{
	init_hashtable(g_main.env_var);
	g_main.token_list = NULL;
	g_main.line = NULL;
	g_main.open_quote = 0;
	g_main.status = 0;
	g_main.is_heredoc_running = 0;
}
