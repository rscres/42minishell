/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/09 11:40:18 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	set_fd_in(t_cmd *cmd)
{
	if (cmd->infile != NULL)
	{
		cmd->fd[0] = open(cmd->infile, O_RDONLY);
		if (cmd->fd[0] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->infile, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	set_fd_out(t_cmd *cmd)
{
	if (cmd->outfile != NULL)
	{
		if (cmd->redir[1] == APPEND)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (cmd->redir[1] == OUTFILE)
			cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd[1] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->outfile, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	exec_builtin(t_cmd *cmd)
{
	int	fd_set[2];

	fd_set[0] = set_fd_in(cmd);
	fd_set[1] = set_fd_out(cmd);
	if (!ft_strcmp(cmd->name, "echo"))
		g_main.status = (ft_echo(cmd->args + 1, cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "cd"))
		g_main.status = (ft_cd(cmd->args));
	else if (!ft_strcmp(cmd->name, "pwd"))
		g_main.status = (ft_pwd(cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "export"))
		g_main.status = (ft_export(cmd->args, cmd->argc, cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "unset"))
		g_main.status = (ft_unset(cmd->args + 1));
	else if (!ft_strcmp(cmd->name, "env"))
		g_main.status = (ft_env(cmd->fd[1]));
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args, cmd->argc);
	if (fd_set[0] == 0)
		close(cmd->fd[0]);
	if (fd_set[1] == 0)
		close(cmd->fd[1]);
	return (0);
}
