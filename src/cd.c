/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 01:24:07 by renato            #+#    #+#             */
/*   Updated: 2023/11/23 15:48:20 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	update_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	update_key(g_main.env_var, "OLDPWD", search(g_main.env_var, "PWD")->value);
	update_key(g_main.env_var, "PWD", dir);
	ft_safe_free(dir);
}

int	ft_cd(char **args)
{
	if (!g_main.cmd_list->argc)
	{
		args[0] = search(g_main.env_var, "HOME")->value;
	}
	if (g_main.cmd_list->argc > 1)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (chdir(args[0]) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd();
	return (0);
}
