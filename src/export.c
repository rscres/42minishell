/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:25:08 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/16 18:32:01 by rseelaen         ###   ########.fr       */
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

static int	set_var(char **args)
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
		else
		{
			ft_putendl_fd("export: not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **args)
{
	if (args[0] == NULL)
		print_vars();
	else
		return (set_var(args));
	return (0);
}
