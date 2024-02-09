/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:09 by igenial           #+#    #+#             */
/*   Updated: 2024/02/08 14:32:03 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ig_pipe(t_cmd *cmd)
{
	int	fd_read;
	int	counter;

	g_main.is_cmd_running = TRUE;
	counter = g_main.pipe->pipe_counter;
	fd_read = dup(STDIN_FILENO);
	ig_pipe_exc(cmd, fd_read);
	close(fd_read);
	while (counter >= 0)
	{
		waitpid(-1, &g_main.status, 0);
		counter--;
	}
	ig_close_linked();
	clear_cmd_list();
	g_main.is_cmd_running = FALSE;
}

void	ig_pipe_fd(t_cmd *cmd, int fd)
{
	pipe(g_main.pipe->fd1);
	if (cmd->name)
		g_main.pipe->path = check_path(cmd->name);
	ig_middle_born(cmd, fd);
	free(g_main.pipe->path);
	dup2(g_main.pipe->fd1[0], fd);
	ig_close_linked();
}

void	ig_middle_born(t_cmd *cmd, int fd)
{
	pid_t	pid;

	pid = fork();
	signal(SIGQUIT, sigquit);
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		if (g_main.pipe->pipe_counter)
			dup2(g_main.pipe->fd1[1], STDOUT_FILENO);
		ig_close_linked();
		close(fd);
		ig_pipe_handler(cmd);
		ig_pipe_closer();
		if (g_main.signal_received)
			g_main.status = 130;
		signal(SIGQUIT, SIG_IGN);
		exit(1);
	}
}

void	ig_pipe_exc(t_cmd *cmd, int fd_read)
{
	while (g_main.pipe->pipe_counter >= 0 && cmd)
	{
		if ((cmd->type == PIPE && !cmd->prev)
			|| (cmd->type == PIPE && cmd->prev->type == PIPE))
		{
			ig_pipe_fd(cmd, fd_read);
			g_main.pipe->pipe_counter--;
		}
		else if (cmd->type == WORD)
		{
			ig_pipe_fd(cmd, fd_read);
			g_main.pipe->pipe_counter--;
		}
		cmd = cmd->next;
	}
}
