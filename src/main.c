/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:19 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/18 15:47:26 by rseelaen         ###   ########.fr       */
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

void	execute_cmd_list(void) // incluir PIPE
{
	t_cmd	*cmd;
	char	*path;

	cmd = g_main.cmd_list;
	while (cmd)
	{
		//______adicionar função separada para exec cmd______
		if (check_if_builtin(cmd->name))
			g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
		else
		{
			path = check_path(cmd->name);
			if (!access(cmd->name, F_OK))
				exec(cmd, cmd->name);
			else if (path)
				exec(cmd, path);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->name, 2);
				ft_putstr_fd(": command not found\n", 2);
				g_main.status = 127;
			}
			ft_safe_free((void **)&path);
			//______adicionar função separada para exec cmd______
		}
		cmd = cmd->next;
	}
}

int	main(__attribute__((unused))int argc, __attribute__((unused))char **argv,
            char **env)
{
	char	*line;

	signal_set();
	init_global();
	set_env(g_main.env_var, env);
	while (369)
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