/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:25:08 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/29 16:06:56 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**save_table_to_array(void)
{
	t_env	*tmp;
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = malloc((TABLE_SIZE + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (i < TABLE_SIZE)
	{
		tmp = g_main.env_var[i];
		while (tmp && tmp->key)
		{
			array[j] = ft_strjoin(tmp->key, "=");
			array[j] = ft_strjoin(array[j], tmp->value);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

//needs rework to print in alphabetical order
static void	print_vars(void)
{
	char	**array;
	int		i;

	i = 0;
	array = save_table_to_array();
	if (!array)
		return ;
	ft_merge_sort(ft_arrlen(array), array);
	while (array[i])
	{
		ft_putstr_fd("declare -x ", 0);
		ft_putendl_fd(array[i], 0);
		i++;
	}
}

static int	is_valid_char(char *str)
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

static int	set_var(char **args)
{
	char	**split;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') && ft_strlen(args[i]) > 1)
		{
			split = ft_split(args[i], '='); //remove ft_split, needs rework for "A='b=c=d' cases"
			if (!split[0] || !is_valid_char(split[0]))
				return (error_msg(split[0]));
			if (!split[1])
				split[1] = ft_strdup("");
			if (search(g_main.env_var, split[0]))
				update_key(g_main.env_var, split[0], split[1]);
			else
				insert_key(g_main.env_var, split[0], split[1]);
			free_tab(split);
		}
		else if (!ft_isalpha(args[i][0]) || is_valid_char(args[i]) == 0)
			return (error_msg(args[i]));
		else
		{
			if (search(g_main.env_var, args[i]))
				update_key(g_main.env_var, args[i], NULL);
			else
				insert_key(g_main.env_var, args[i], NULL);
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
