/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:25:08 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/15 22:20:35 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//needs rework
static void	print_vars(void)
{
	int	i;

	i = 0;
	while (g_main.env_var[i])
	{
		ft_putstr_fd("declare -x ", 0);
		ft_putstr_fd(g_main.env_var[i]->key, 0);
		ft_putchar_fd('=', 0);
		ft_putendl_fd(g_main.env_var[i]->value, 0);
		i++;
	}
}

static void	set_var(char **args)
{
	char	**split;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			split = ft_split(args[i], '=');
			if (search(g_main.env_var, split[0]))
				update_key(g_main.env_var, split[0], split[1]);
			else
				insert_key(g_main.env_var, split[0], split[1]);
		}
		i++;
	}
}

int	ft_export(char **args)
{
	if (args[0] == NULL)
		print_vars();
	else
		set_var(args);
	return (0);
}
