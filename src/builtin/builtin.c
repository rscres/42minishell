/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2024/01/31 00:19:58 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr(cwd);
	ft_putchar('\n');
	ft_safe_free((void **)&cwd);
	return (0);
}

int	ft_unset(char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (args[i])
	{
		delete_key(g_main.env_var, args[i]);
		i++;
	}
	return (ret);
}

int	ft_env(void)
{
	print_hashtable(g_main.env_var);
	return (0);
}

void	backup_fd(int backup[2])
{
	backup[0] = dup(0);
	backup[1] = dup(1);
}

void	restore_fd(int backup[2])
{
	dup2(backup[0], 0);
	dup2(backup[1], 1);
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
		g_main.status = (ft_export(cmd->args + 1, cmd->argc));
	else if (!ft_strcmp(cmd->name, "unset"))
		g_main.status = (ft_unset(cmd->args + 1));
	else if (!ft_strcmp(cmd->name, "env"))
		g_main.status = (ft_env());
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args, cmd->argc);
	else if (!ft_strcmp(cmd->name, "<<"))
		heredoc(cmd->args[0]);
	restore_fd(backup);
	return (0);
}
