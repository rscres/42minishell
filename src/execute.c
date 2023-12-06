/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:32:42 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/06 19:28:43 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static void	redir_error(t_token *token)
// {
// 	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
// 	ft_putstr_fd(token->content, 2);
// 	ft_putstr_fd("'\n", 2);
// 	g_main.status = 1;
// }

// static void	redir_2(t_token *token, t_cmd *cmd)
// {
// 	int			fd;

// 	if (token->type == REDIR)
// 	{
// 		if (token->next && token->next->type == WORD)
// 		{
// 			fd = open(token->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 			{
// 				ft_putstr_fd("minishell: ", 2);
// 				ft_putstr_fd(token->next->content, 2);
// 				ft_putstr_fd(": ", 2);
// 				ft_putstr_fd(strerror(errno), 2);
// 				ft_putstr_fd("\n", 2);
// 				g_main.status = 1;
// 				return ;
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			redir_2(token->next->next, cmd);
// 		}
// 	}
// }

// static void	redir_1(t_token *token, t_cmd *cmd)
// {
// 	int			fd;

// 	if (token->type == REDIR)
// 	{
// 		if (token->next && token->next->type == WORD)
// 		{
// 			fd = open(token->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 			{
// 				ft_putstr_fd("minishell: ", 2);
// 				ft_putstr_fd(token->next->content, 2);
// 				ft_putstr_fd(": ", 2);
// 				ft_putstr_fd(strerror(errno), 2);
// 				ft_putstr_fd("\n", 2);
// 				g_main.status = 1;
// 				return ;
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			redir_1(token->next->next, cmd);
// 		}
// 	}
// }

// static void	redir(t_cmd *cmd)
// {
// 	t_token		*token;

// 	token = cmd->token;
// 	while (token)
// 	{
// 		if (token->type == REDIR)
// 		{
// 			if (token->next && token->next->type == WORD)
// 			{
// 				if (token->next->next && token->next->next->type == WORD)
// 					redir_2(token, cmd);
// 				else
// 					redir_1(token, cmd);
// 			}
// 			else
// 				redir_error(token->next);
// 		}
// 		token = token->next;
// 	}
// }

// static void	pipe_exec(t_cmd *cmd)
// {
// 	int			pipefd[2];
// 	pid_t		pid;

// 	if (pipe(pipefd) == -1)
// 	{
// 		ft_putstr_fd("pipe error\n", 2);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		ft_putstr_fd("fork error\n", 2);
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[1]);
// 		redir(cmd);
// 		execve(cmd->path, cmd->args, g_main.env_var->env);
// 		ft_putstr_fd("execve error\n", 2);
// 		exit(1);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 	}
// }

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
	return (NULL);
}

static void	exec(t_cmd *cmd, char *path)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
	if (pid == 0)
	{
		redir(cmd);
		execve(path, cmd->args, NULL);
		ft_putstr_fd("execve error\n", 2);
		exit(1);
	}
	else
		waitpid(pid, &g_main.status, 0);
}

int	check_if_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

void	execute_cmd_list(void)
{
	t_cmd	*cmd;
	char	*path;

	cmd = g_main.cmd_list;
	while (cmd)
	{
		if (check_if_builtin(cmd->name))
			g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
		else
		{
			path = check_path(cmd->name);
			if (path)
				exec(cmd, path);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->name, 2);
				ft_putstr_fd(": command not found\n", 2);
				g_main.status = 127;
			}
			ft_safe_free((void **)&path);
		}
		cmd = cmd->next;
	}
}
