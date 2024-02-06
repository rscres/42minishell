/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:09 by igenial           #+#    #+#             */
/*   Updated: 2024/01/09 11:20:13 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ig_middle_born(t_cmd *cmd, int fd);
void	ig_pipe_executer(t_cmd *cmd, int fd);
void	ig_middle_pipes(t_cmd *cmd);
void	ig_edge_pipes(t_cmd *cmd);

void	ig_close_linked(void)
{
	close(g_main.pipe->fd1[0]); // Close reading end of the pipe
	close(g_main.pipe->fd1[1]); // Close writing end of the pipe
}

void	ig_pipe(t_cmd *cmd)
{
	int	fd_read;
	int	counter;
	int	i;

	counter = g_main.pipe->pipe_counter;
	fd_read = dup(STDIN_FILENO);
	while (g_main.pipe->pipe_counter + 1)
	{
		if (cmd->type == WORD)
		{
			ig_pipe_executer(cmd, fd_read);
			g_main.pipe->pipe_counter--;
		}
		cmd = cmd->next;
	}
	close(fd_read);
	i = 0;
	while (i < counter + 1)
	{
		waitpid(-1, &g_main.status, 0);
		i++;
	}
	ig_close_linked();
	clear_cmd_list();
	ft_safe_free((void **)&g_main.pipe->path);
}

void	ig_pipe_executer(t_cmd *cmd, int fd)
{
	char	*tmp;

	pipe(g_main.pipe->fd1);
	tmp = g_main.pipe->path;
	g_main.pipe->path = check_path(cmd->name);
	free(tmp);
	ig_middle_born(cmd, fd);
	dup2(g_main.pipe->fd1[0], fd);
	close(g_main.pipe->fd1[0]);
	close(g_main.pipe->fd1[1]);
}

void	ig_middle_born(t_cmd *cmd, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		if (g_main.pipe->pipe_counter)
			dup2(g_main.pipe->fd1[1], STDOUT_FILENO);
		close(g_main.pipe->fd1[0]);
		close(g_main.pipe->fd1[1]);
		close(fd);
		if (check_if_builtin(cmd->name))
		{
			g_main.status = exec_builtin(cmd);
			clear_hashtable(g_main.env_var);
			ft_safe_free((void **)&g_main.pipe->path);
			ft_safe_free((void **)&g_main.pipe);
			clear_cmd_list();
			exit(g_main.status);
		}
		else
		{
			set_fd(cmd);
			execve(g_main.pipe->path, cmd->args, g_main.envp);
			ft_putstr_fd("execve error\n", 2);
			clear_cmd_list();
			clear_hashtable(g_main.env_var);
		}
		ig_close_linked();
		ft_safe_free((void **)&g_main.pipe->path);
		ft_safe_free((void **)&g_main.pipe);
		exit(1);
	}
}

void	ig_open_linked(void)
{
	pipe(g_main.pipe->fd1);
}
