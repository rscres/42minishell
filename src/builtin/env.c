/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:42:26 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/06 13:09:36 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (1);
	while (tab[i])
		ft_safe_free((void **)&tab[i++]);
	ft_safe_free((void **)&tab);
	return (i);
}

int	set_env(t_env **env_var, char **env)
{
	char	**arg;
	int		i;

	i = 0;
	while (env[i])
	{
		arg = split_var(env[i]);
		if (arg[0] && arg[1])
			insert_key(env_var, arg[0], arg[1]);
		free_tab(arg);
		i++;
	}
	return (1);
}

int	ft_env(int fd)
{
	print_hashtable(g_main.env_var, fd);
	return (0);
}
