/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:19 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/29 16:18:55 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_main	g_main;

void	print_ascii(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execl("/usr/bin/clear", "clear", NULL); //change to execve
		exit(0);
	}
	else
		wait(NULL);
	ft_putstr("░  ░░░░  ░        ░   ░░░  ░        ░  ░░░░  ░        ░");
	ft_putendl_fd("  ░░░░░░░  ░░░░░░░", 0);
	ft_putstr("▒   ▒▒   ▒▒▒▒  ▒▒▒▒    ▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒");
	ft_putendl_fd("  ▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒", 0);
	ft_putstr("▓        ▓▓▓▓  ▓▓▓▓  ▓  ▓  ▓▓▓▓  ▓▓▓▓        ▓      ▓▓▓");
	ft_putendl_fd("  ▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓", 0);
	ft_putstr("█  █  █  ████  ████  ██    ████  ████  ████  █  ███████");
	ft_putendl_fd("  ███████  ███████", 0);
	ft_putstr("█  ████  █        █  ███   █        █  ████  █        ");
	ft_putendl_fd("█        █        █", 0);
	ft_putchar_fd('\n', 0);
}

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
	return (line);
}

int	main(__attribute__((unused))int argc, __attribute__((unused))char **argv,
            char **env)
{
	char	*line;

	print_ascii();
	signal_set();
	init_global(env);
	set_env(g_main.env_var, env);
	while (369)
	while (369)
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
			execute_cmd_list();
			clear_cmd_list();
			add_history(g_main.line);
		}
		if (g_main.line)
			ft_safe_free((void **)&g_main.line);
	}
	return (g_main.status);
}
