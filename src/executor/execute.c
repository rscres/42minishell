/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:32:42 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/02 12:27:51 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

char	*check_path(char *name)
{
	char		*path;
	char		**paths;
	int			i;

	i = -1;
	path = search_value(g_main.env_var, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(path, name);
		if (!access(path, F_OK))
		{
			free_tab(paths);
			return (path);
		}
		ft_safe_free((void **)&path);
	}
	free_tab(paths);
	return (ft_strdup(name));
}

int	ft_error(char *str, char *msg, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	g_main.status = err;
	return (err);
}

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

void	sigquit(int sig)
{
	(void)sig;
	if (g_main.is_cmd_running)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_main.status = 131;
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_main.status = 130;
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
		signal(SIGQUIT, SIG_IGN);
	}
}

int	check_if_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0 || ft_strcmp(name, "<<") == 0)
		return (1);
	return (0);
}

int is_directory(const char *path) //need refactoring
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	execute_cmd_list(void)
{
	t_cmd	*cmd;
	char	*path;
	int		fd;

	cmd = g_main.cmd_list;
	fd = 0;
	while (cmd && g_main.pipe->pipe_counter == 0)
	{
		if (cmd->type == WORD)
		{
			g_main.is_cmd_running = 1;
			if (cmd->infile)
			{
				fd = open(cmd->infile, O_RDONLY);
				if (fd == -1)
				{
					ft_error(cmd->infile, NULL, 1);
					return ;
				}
				close(fd);
			}
			if (is_directory(cmd->name))
			{	
				ft_error(cmd->name, "is a directory", 126);
				return ;
			}
			path = check_path(cmd->name);
			if (check_if_builtin(cmd->name))
			{
				// ft_safe_free((void **)&path);
				exec_builtin(cmd);
			}
			else if (!access(path, F_OK))
				exec(cmd, path);
			else if (!access(cmd->name, F_OK))
				exec(cmd, cmd->name);
			else
				ft_error(cmd->name, "command not found", 127);
			ft_safe_free((void **)&path);
			g_main.is_cmd_running = 0;
		}
		cmd = cmd->next;
	}
	// printf("\n\n > %d <\n\n", g_main.pipe->pipe_counter);
	if (g_main.pipe->pipe_counter != 0)
	{	
		ig_pipe(cmd);
	}
	heredoc_files(REMOVE);
	clear_cmd_list();
}
