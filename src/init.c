/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:06:47 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/19 18:06:32 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	init_hashtable(t_env **env_var)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
		env_var[i++] = NULL;
}

void ig_pipe_init (void)
{
	g_main.pipe = ft_calloc(1, sizeof(t_pipe_info));
}

void	init_global(char **envp)
{
	init_hashtable(g_main.env_var);
	ig_pipe_init();
	g_main.token_list = NULL;
	g_main.line = NULL;
	g_main.envp = envp;
	g_main.open_quote = 0;
	g_main.status = 0;
	g_main.is_cmd_running = FALSE;
	g_main.signal_received = FALSE;
}
