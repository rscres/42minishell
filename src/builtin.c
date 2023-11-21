/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/21 02:16:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr(cwd);
	ft_putchar('\n');
	free(cwd);
	return (0);
}

int	ft_cd(char **args)
{
	int	ret;

	ret = 0;
	if (!g_main.cmd_list->argc)
	{
		if ((ret = chdir(getenv("HOME"))) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else if (g_main.cmd_list->argc > 1)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else
	{
		if ((ret = chdir(args[0])) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (args[i])
	{
		//delete after implementing variable expansion
		if (!ft_strcmp(args[i], "$?"))
		{
			ft_putnbr_fd(g_main.status, fd);
			i++;
			continue ;
		}
		if (!ft_strcmp(args[i], "-n")) //fix for multiple -n and -nnnnnn
		{
			n_flag = 1;
			i++;
			continue ;
		}
		if (args[i] != NULL && ft_strcmp(args[i], ""))
			ft_putstr_fd(args[i], fd);
		if (args[i + 1] != NULL && ft_strcmp(args[i], ""))
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
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

int	exec_builtin(char *name, char **args, int argc)
{
	if (!ft_strcmp(name, "echo"))
		return (ft_echo(args, 1));
	else if (!ft_strcmp(name, "cd"))
		return (ft_cd(args));
	else if (!ft_strcmp(name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(name, "export"))
		return (ft_export(args));
	else if (!ft_strcmp(name, "unset"))
		return (ft_unset(args));
	else if (!ft_strcmp(name, "env"))
		return (ft_env());
	else if (!ft_strcmp(name, "exit"))
		ft_exit(args, argc);
	return (0);
}
