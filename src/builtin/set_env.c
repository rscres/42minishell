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
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (i);
}

int	set_env(t_env **env_var, char **env)
{
	char	**arg;
	int		i;

	i = 0;
	while (env[i])
	{
		arg = ft_split(env[i], '=');
		if (arg[0] && arg[1])
			insert_key(env_var, arg[0], arg[1]);
		free_tab(arg);
		i++;
	}
	return (1);
}
