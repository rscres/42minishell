/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 01:24:07 by renato            #+#    #+#             */
/*   Updated: 2024/02/05 20:18:10 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	update_pwd(char *backup)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!search(g_main.env_var, "OLDPWD"))
		insert_key(g_main.env_var, "OLDPWD", backup);
	else
		update_key(g_main.env_var, "OLDPWD", search_value(g_main.env_var, "PWD"));
	if (!search(g_main.env_var, "PWD"))
		insert_key(g_main.env_var, "PWD", dir);
	else
		update_key(g_main.env_var, "PWD", dir);
	ft_safe_free((void **)&dir);
}

char	*get_home(void)
{
	t_env	*home;

	home = search(g_main.env_var, "HOME");
	if (home == NULL)
		return (NULL);
	return (home->value);
}

int	ft_cd(char **args)
{
	int		ret = 0;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	ret = 0;
	if (g_main.cmd_list->argc > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (g_main.cmd_list->argc <= 1)
		ret = chdir(get_home());
	else if (g_main.cmd_list->argc == 2)
		ret = chdir(args[1]);
	if (ret != 0)
	{
		if (search(g_main.env_var, "HOME") == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		else
			perror("cd");
		ft_safe_free((void **)&oldpwd);
		return (1);
	}
	update_pwd(oldpwd);
	ft_safe_free((void **)&oldpwd);
	return (0);
}
