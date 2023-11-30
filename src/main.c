/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:19 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/30 18:16:44 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_main	g_main;

// char	*get_line(int flag)
// {
// 	char	*line;

// 	if (flag == 1)
// 		line = readline("> ");
// 	else
// 		line = readline("minishell$ ");
// 	if (line)
// 		add_history(line);
// 	return (line);
// }

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
	if (line)
		add_history(line);
	return (line);
}

int	main(__attribute__((unused))int argc, __attribute__((unused))char **argv,
	char **env)
{
	char	*line;

	signal_set();
	init_global();
	set_env(g_main.env_var, env);
	while (1)
	{
		line = get_line();
		if (!line)
			ft_exit2(g_main.status);
		if (ft_strlen(line) > 0)
		{
			g_main.line = line;
			lexer(&line);
			parser();
			execute_cmd_list();
			clear_token_list();
			clear_cmd_list();
			add_history(g_main.line);
		}
		ft_safe_free((void **)&line);
	}
	return (g_main.status);
}
