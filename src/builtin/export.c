/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:25:08 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/18 14:35:34 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//needs rework to print in alphabetical order
static void	print_vars(void)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (g_main.env_var[i] && g_main.env_var[i]->key)
		{
			ft_putstr_fd("declare -x ", 0);
			ft_putstr_fd(g_main.env_var[i]->key, 0);
			ft_putchar_fd('=', 0);
			ft_putendl_fd(g_main.env_var[i]->value, 0);
		}
		i++;
	}
}

static int	str_isalnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	error_msg(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}


//
static int	set_var(char **args)
{
	char	**split;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') && ft_strlen(args[i]) > 1)
		{
			split = ft_split(args[i], '=');
			if (!split[0] || !str_isalnum(split[0]))
				return (error_msg(split[0]));
			if (!split[1])
				split[1] = ft_strdup("");
			if (search(g_main.env_var, split[0]))
				update_key(g_main.env_var, split[0], split[1]);
			else
				insert_key(g_main.env_var, split[0], split[1]);
			free_tab(split);
		}
		else
		{
			if (!ft_isalpha(args[i][0]) || str_isalnum(args[i]) == 0)
				return (error_msg(args[i]));
		}
		i++;
	}
	return (0);
}

int	ft_export(char **args, int argc)
{
	if (argc < 2)
		print_vars();
	else
		return (set_var(args));
	return (0);
}
