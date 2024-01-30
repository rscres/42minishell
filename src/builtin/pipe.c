/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:09 by igenial           #+#    #+#             */
/*   Updated: 2024/01/29 17:33:03 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void ig_first_born(t_cmd *cmd);
void ig_last_born(t_cmd *cmd);
void ig_open_linked(void);
void ig_middle_born(t_cmd *cmd, int fd);
//int *ig_define_pipe(int *fd);
void ig_middle_pipes(t_cmd *cmd);
void ig_edge_pipes(t_cmd *cmd);

void ig_pipe(t_cmd *cmd)
{
	int fd_read;

	fd_read = dup(STDIN_FILENO);
	while (g_main.pipe->pipe_counter + 1) {
		pipe(g_main.pipe->fd1);
		g_main.pipe->path = check_path(cmd->name);
		ig_middle_born(cmd, fd_read);
		dup2(g_main.pipe->fd1[0], fd_read);
		close(g_main.pipe->fd1[0]);
		close(g_main.pipe->fd1[1]);
		cmd = cmd->next;
		while (cmd->type != WORD && cmd)
			cmd = cmd->next;
		g_main.pipe->pipe_counter--;
	}
	close(fd_read);
}
//void ig_first_born(t_cmd *cmd)
//{
//	pid_t pid;
//
//	pid = fork();
//	if (pid == 0)
//	{
//		close(g_main.pipe->fd1[0]);
//		dup2(g_main.pipe->fd1[1], STDOUT_FILENO);
//		close(g_main.pipe->fd1[1]);
//		if (check_if_builtin(cmd->name))
//			g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
//		else
//		{
//			execve(g_main.pipe->path, cmd->args, NULL);
//			ft_putstr_fd("execve error\n", 2);
//		}
//		exit(1);
//	}
//}
//void ig_last_born(t_cmd *cmd)
//{
//	pid_t pid;
//
//	pid = fork();
//	if (pid == 0)
//	{
//		close(g_main.pipe->fd1[1]);
//		dup2(g_main.pipe->fd1[0], STDIN_FILENO);
//		close(g_main.pipe->fd1[0]);
//		printf("\n\n__recebe__\n\n");
//		if (check_if_builtin(cmd->name))
//			g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
//		else
//			execve(g_main.pipe->path, cmd->args, NULL);
//		ft_putstr_fd("execve error\n", 2);
//		exit(1);
//	}
//
//}
void ig_middle_born(t_cmd *cmd, int fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		printf("\n\n__ M recebe %s__\n\n", cmd->name);
		dup2(fd, STDIN_FILENO);
		if (g_main.pipe->pipe_counter)
			dup2(g_main.pipe->fd1[1], STDOUT_FILENO);
		close(g_main.pipe->fd1[0]);
		close(g_main.pipe->fd1[1]);
		close(fd);
		if (check_if_builtin(cmd->name)) {
			g_main.status = exec_builtin(cmd);
		}
		else
		{
			execve(g_main.pipe->path, cmd->args, g_main.envp);
			ft_putstr_fd("execve error\n", 2);
		}
		exit(1);
	}
}

void ig_open_linked(void)
{
		pipe(g_main.pipe->fd1);
}


//int *ig_define_pipe(int *fd)
//{
//	if(!g_main.pipe->fd1->used)
//	{
//		fd = g_main.pipe->fd1->pipes;
//		g_main.pipe->fd1->used = TRUE;
//	}
//	else if(!g_main.pipe->fd2->used)
//	{
//		fd = g_main.pipe->fd2->pipes;
//		g_main.pipe->fd2->used = TRUE;
//	}
//	else if(!g_main.pipe->fd3->used)
//	{
//		fd = g_main.pipe->fd3->pipes;
//		g_main.pipe->fd3->used = TRUE;
//	}
//	return (fd);
//}

//void ig_edge_pipes(t_cmd *cmd)
//{
//	if(!cmd->prev)
//	{
//		if (check_if_builtin(cmd->name))
//			ig_first_born(cmd);
//		g_main.pipe->path = check_path(cmd->name);
//		if (access(cmd->name, F_OK))
//			ig_first_born(cmd);
//	}
//	else if(!cmd->next)
//	{
//		if (check_if_builtin(cmd->name))
//			ig_last_born(cmd);
//		g_main.pipe->path = check_path(cmd->name);
//		if (access(cmd->name, F_OK))
//			ig_last_born(cmd);
//	}
//}


