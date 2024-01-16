/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:06:47 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/16 00:22:06 by renato           ###   ########.fr       */
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

void	init_global(char **envp)
{
	init_hashtable(g_main.env_var);
	g_main.token_list = NULL;
	g_main.line = NULL;
	g_main.envp = envp;
	g_main.open_quote = 0;
	g_main.status = 0;
	g_main.is_cmd_running = 0;
}
