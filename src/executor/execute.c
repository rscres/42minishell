/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:32:42 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/05 22:30:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//Need flag to know if output is outfile or append
void	set_fd(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		cmd->fd[0] = open(cmd->infile, O_RDONLY);
		if (cmd->fd[0] == -1)
		{
			ft_error(cmd->infile, NULL, 1);
			exit(1);
		}
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
	}
	if (cmd->outfile != NULL)
	{
		if (cmd->redir[1] == APPEND)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_APPEND, 0644);
		else if (cmd->redir[1] == OUTFILE)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_TRUNC, 0644);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}

void	exec(t_cmd *cmd, char *path)
{
	int		pid;

	pid = fork();
	signal(SIGQUIT, sigquit);
	if (pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
	if (pid == 0)
	{
		set_fd(cmd);
		if (execve(path, cmd->args, g_main.envp) == -1)
			ft_putstr_fd("execve error\n", 2);
		exit(1);
	}
	else
	{
		waitpid(pid, &g_main.status, 0);
		if (g_main.signal_received)
			g_main.status = 130;
		signal(SIGQUIT, SIG_IGN);
	}
}

void	simple_command(t_cmd *cmd)
{
	char	*path;

	g_main.is_cmd_running = 1;
	if (file_dir_check(cmd))
	{
		g_main.is_cmd_running = 0;
		return ;
	}
	path = check_path(cmd->name);
	if (check_if_builtin(cmd->name))
	{
		ft_safe_free((void **)&path);
		exec_builtin(cmd);
	}
	else if (path && !access(path, F_OK))
		exec(cmd, path);
	else
		ft_error(cmd->name, "command not found", 127);
	ft_safe_free((void **)&path);
	g_main.is_cmd_running = 0;
}

void	execute_cmd_list(void)
{
	t_cmd	*cmd;

	cmd = g_main.cmd_list;
	if (!cmd)
		return ;
	if (g_main.pipe->pipe_counter == 0)
		simple_command(cmd);
	if (g_main.pipe->pipe_counter != 0)
		ig_pipe(cmd);
	heredoc_files(REMOVE);
	clear_cmd_list();
}
