/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 01:24:07 by renato            #+#    #+#             */
/*   Updated: 2023/11/28 19:08:03 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	update_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	update_key(g_main.env_var, "OLDPWD", search(g_main.env_var, "PWD")->value);
	update_key(g_main.env_var, "PWD", dir);
	ft_safe_free((void **)&dir);
}

int	ft_cd(char **args)
{
	if (g_main.cmd_list->argc <= 1)
	{
		args[1] = search(g_main.env_var, "HOME")->value;
	}
	if (g_main.cmd_list->argc > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd();
	return (0);
}
