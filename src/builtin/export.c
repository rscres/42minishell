/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:25:08 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/05 22:51:46 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_valid_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		else if (!ft_isalnum(str[i]) && str[i] != '_')
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

char	**split_var(char *var)
{
	char	**split;

	split = ft_calloc(3, sizeof(char *));
	if (!split)
		return (NULL);
	if (ft_strchr(var, '=') && var[ft_strlen(var) - 1] != '=')
	{
		split[0] = ft_strndup(var, ft_strchr(var, '=') - var);
		split[1] = ft_strdup(ft_strchr(var, '=') + 1);
	}
	else
	{
		if (var[ft_strlen(var) - 1] == '=')
			split[0] = ft_strndup(var, ft_strlen(var) - 1);
		else
			split[0] = ft_strdup(var);
		split[1] = ft_strdup("");
	}
	return (split);
}

static int	set_var(char **args)
{
	char	**split;
	int		i;

	i = 1;
	while (args[i])
	{
		if ((ft_strchr(args[i], '=') && ft_strlen(args[i]) > 1)
			|| is_valid_char(args[i]))
		{
			split = split_var(args[i]);
			if (!split[0] || !is_valid_char(split[0]))
				return (error_msg(split[0]));
			if (search(g_main.env_var, split[0]))
				update_key(g_main.env_var, split[0], split[1]);
			else
				insert_key(g_main.env_var, split[0], split[1]);
			free_tab(split);
		}
		else if (!ft_isalpha(args[i][0]) || is_valid_char(args[i]) == 0)
			return (error_msg(args[i]));
		i++;
	}
	return (0);
}

int	ft_export(char **args, int argc, int fd)
{
	if (argc < 2)
		print_vars(fd);
	else
		return (set_var(args));
	return (0);
}
