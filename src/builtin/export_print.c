/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:44:21 by renato            #+#    #+#             */
/*   Updated: 2024/02/09 13:14:24 by rseelaen         ###   ########.fr       */
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
			array[j] = ft_strjoin_free(array[j], tmp->value);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

void	print(char **tmp, int fd)
{
	if (ft_strcmp(tmp[0], "_") == 0)
		return ;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(tmp[0], fd);
	if (tmp[1])
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(tmp[1] + 1, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putchar_fd('\n', fd);
}

void	print_vars(int fd)
{
	char	**array;
	char	**tmp;
	int		i;

	i = 0;
	signal(SIGPIPE, SIG_IGN);
	array = save_table_to_array();
	if (!array)
		return ;
	tmp = malloc(sizeof(char *) * 2);
	ft_merge_sort(ft_arrlen(array), array);
	while (array && array[i])
	{
		tmp[1] = ft_strdup(ft_strchr(array[i], '='));
		tmp[0] = ft_strndup(array[i], ft_strlen(array[i])
				- ft_strlen(tmp[1]));
		print(tmp, fd);
		ft_safe_free((void **)&tmp[0]);
		ft_safe_free((void **)&tmp[1]);
		i++;
	}
	ft_safe_free((void **)&tmp);
	free_tab(array);
	signal(SIGPIPE, SIG_DFL);
}
