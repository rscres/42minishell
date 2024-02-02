/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/02 01:51:14 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	backup_fd(int backup[2])
{
	backup[0] = dup(0);
	backup[1] = dup(1);
}

void	restore_fd(int backup[2])
{
	dup2(backup[0], 0);
	close(backup[0]);
	dup2(backup[1], 1);
	close(backup[1]);
}

void	prep_exit(t_cmd *cmd, int backup[2])
{
	restore_fd(backup);
	close(0);
	close(1);
	ft_exit(cmd->args, cmd->argc);
}

int	exec_builtin(t_cmd *cmd)
{
	int	backup[2];

	backup_fd(backup);
	set_fd(cmd);
	if (!ft_strcmp(cmd->name, "echo"))
		g_main.status = (ft_echo(cmd->args + 1, 1));
	else if (!ft_strcmp(cmd->name, "cd"))
		g_main.status = (ft_cd(cmd->args));
	else if (!ft_strcmp(cmd->name, "pwd"))
		g_main.status = (ft_pwd());
	else if (!ft_strcmp(cmd->name, "export"))
		g_main.status = (ft_export(cmd->args, cmd->argc));
	else if (!ft_strcmp(cmd->name, "unset"))
		g_main.status = (ft_unset(cmd->args + 1));
	else if (!ft_strcmp(cmd->name, "env"))
		g_main.status = (ft_env());
	else if (!ft_strcmp(cmd->name, "exit"))
		prep_exit(cmd, backup);
	else if (!ft_strcmp(cmd->name, "<<"))
		heredoc(cmd->args[0]);
	restore_fd(backup);
	return (0);
}
