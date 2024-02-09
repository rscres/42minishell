/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:34:52 by igenial           #+#    #+#             */
/*   Updated: 2024/02/09 13:48:26 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ig_close_linked(void)
{
	close(g_main.pipe->fd1[0]);
	close(g_main.pipe->fd1[1]);
}

void	ig_pipe_closer(void)
{
	clear_cmd_list();
	clear_hashtable(g_main.env_var);
	ig_close_linked();
	ft_safe_free((void **) &g_main.pipe->path);
	ft_safe_free((void **) &g_main.pipe);
	free(g_main.line);
	close(0);
	close(1);
	close(2);
}

void	ig_pipe_handler(t_cmd *cmd)
{
	if (file_dir_check(cmd))
	{
		ig_pipe_closer();
		exit(1);
	}
	if (check_if_builtin(cmd->name))
	{
		g_main.status = exec_builtin(cmd);
		ig_pipe_closer();
		exit(g_main.status);
	}
	else if (g_main.pipe->path && !access(g_main.pipe->path, F_OK))
	{
		set_fd(cmd);
		if (execve(g_main.pipe->path, cmd->args, g_main.envp) == -1)
			ft_putstr_fd("execve error\n", 2);
	}
	else if (cmd->type != PIPE)
		ft_error(cmd->name, "command not found", 127);
}
