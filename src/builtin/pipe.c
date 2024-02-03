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

void ig_middle_born(t_cmd *cmd, int fd);
void ig_pipe_executer(t_cmd *cmd, int fd);


void ig_pipe(t_cmd *cmd)
{
	int fd_read;

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
	clear_cmd_list();
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

void ig_middle_born(t_cmd *cmd, int fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		if (g_main.pipe->pipe_counter)
			dup2(g_main.pipe->fd1[1], STDOUT_FILENO);
		close(g_main.pipe->fd1[0]);
		close(g_main.pipe->fd1[1]);
		close(fd);
		if (check_if_builtin(cmd->name)) {
			g_main.status = exec_builtin(cmd);
			clear_hashtable(g_main.env_var);
			clear_token_list();
			clear_cmd_list();
			ft_safe_free((void**)&g_main.pipe->path); // leaks
			ft_safe_free((void**)&g_main.pipe); // leaks
		}
		else
		{
			execve(g_main.pipe->path, cmd->args, g_main.envp);
			ft_putstr_fd("execve error\n", 2);
		}
		exit(1);
	}
	else
		waitpid(pid, &g_main.status, 0);
}

int ig_select_cat ();

