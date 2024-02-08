/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:19 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/07 17:16:08 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_main	g_main;

char	*get_line(void)
{
	char	*line;

	line = readline("msh$ ");
	if (!line)
		return (NULL);
	while (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\\')
	{
		line[ft_strlen(line) - 1] = '\0';
		line = ft_strjoin(line, readline("> "));
	}
	return (line);
}

int	main(__attribute__((unused))int argc, __attribute__((unused))char **argv,
			char **env)
{
	char	*line;

	init_shell(env);
	while (1)
	{
		g_main.signal_received = FALSE;
		line = get_line();
		if (!line)
		{
			ft_safe_free((void **)&line);
			ft_exit(NULL, 0);
		}
		if (ft_strlen(line) > 0)
		{
			g_main.line = line;
			lexer(&line);
			parser();
			//print_cmd_list();
			execute_cmd_list();
			add_history(g_main.line);
		}
		if (g_main.line)
			ft_safe_free((void **)&g_main.line);
	}
	return (g_main.status);
}
