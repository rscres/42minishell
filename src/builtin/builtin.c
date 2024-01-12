/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/29 15:22:00 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int	exec_builtin(char *name, char **args, int argc)
{
	if (!ft_strcmp(name, "echo"))
		return (ft_echo(args + 1, 1));
	else if (!ft_strcmp(name, "cd"))
		return (ft_cd(args));
	else if (!ft_strcmp(name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(name, "export"))
		return (ft_export(args + 1, argc));
	else if (!ft_strcmp(name, "unset"))
		return (ft_unset(args + 1));
	else if (!ft_strcmp(name, "env"))
		return (ft_env());
	else if (!ft_strcmp(name, "exit"))
		ft_exit(args, argc);
	else if (!ft_strcmp(name, "<<"))
		heredoc(args[0]);
	return (0);
}
