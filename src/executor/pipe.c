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

#include "../../includes/shell.h"

void ig_pipe_execute_cmd(void);
void ig_pipe_executer(t_cmd *cmd, int fd);
void ig_middle_pipes(t_cmd *cmd);
void ig_edge_pipes(t_cmd *cmd);

void ig_pipe(t_cmd *cmd)
{
	int fd_read;

	fd_read = dup(STDIN_FILENO);
	while (g_main.pipe->pipe_counter + 1)
	{
		if (cmd->type == WORD)
		{
			ig_pipe_executer(cmd, fd_read);
//			pipe(g_main.pipe->fd1);
//			g_main.pipe->path = check_path(cmd->name);
//			ig_middle_born(cmd, fd_read);
//			dup2(g_main.pipe->fd1[0], fd_read);
//			close(g_main.pipe->fd1[0]);
//			close(g_main.pipe->fd1[1]);
			g_main.pipe->pipe_counter--;
		}
		cmd = cmd->next;
	}
	close(fd_read);
	clear_cmd_list();
}

void ig_middle_born(t_cmd *cmd, int fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		printf("\n\n__ M recebe %s__\n\n", cmd->name);
		dup2(fd, STDIN_FILENO);
		ig_pipe_execute_cmd(cmd, fd);
		exit(1);
	}
	else
	{
		waitpid(pid, &g_main.status, 0);
	}
}

void ig_pipe_executer(t_cmd *cmd, int fd)
{
	char *tmp;
	pipe(g_main.pipe->fd1);
	tmp = g_main.pipe->path;
	g_main.pipe->path = check_path(cmd->name);
	free(tmp);
	ig_middle_born(cmd, fd);
	dup2(g_main.pipe->fd1[0], fd);
	close(g_main.pipe->fd1[0]);
	close(g_main.pipe->fd1[1]);
}


void	ig_pipe_execute_cmd(void)
{
	t_cmd *cmd;
	char *path;
	int fd;

	cmd = g_main.cmd_list;
	fd = 0;
	while (cmd) {
		if (cmd->type == WORD) {
			g_main.is_cmd_running = 1;
			if (cmd->infile) {
				fd = open(cmd->infile, O_RDONLY);
				if (fd == -1) {
					ft_error(cmd->infile, NULL, 1);
					return;
				}
				close(fd);
			}
			if (is_directory(cmd->name)) {
				ft_error(cmd->name, "is a directory", 126);
				return;
			}
			path = check_path(cmd->name);
			if (check_if_builtin(cmd->name))
			{
				exec_builtin(cmd);
			}
			else if (!access(path, F_OK))
			{
				signal(SIGQUIT, sigquit);
				set_fd(cmd);
				if (execve(path, cmd->args, g_main.envp) == -1)
					ft_putstr_fd("execve error\n", 2);
			}
			else
				ft_error(cmd->name, "command not found", 127);
			ft_safe_free((void **) &path);
			g_main.is_cmd_running = 0;
		}
		cmd = cmd->next;
	}
	heredoc_files(REMOVE);
	clear_cmd_list();
}
void ig_open_linked(void)
{
	pipe(g_main.pipe->fd1);
}