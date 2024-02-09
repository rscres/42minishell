/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:59:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/09 11:42:19 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//This function receives a key as a string and returns a hash value.
//The hash is calculated by adding then multiplying the ASCII values of the
//each character in the string. The result is then multiplied by itself.
//The result is then modulated by the size of the hashtable to find its index.
int	hash(char *key)
{
	u_int64_t	i;

	i = 0;
	while (*key)
	{
		i += *key;
		i *= *key;
		key++;
	}
	i *= i;
	return ((int)(i % TABLE_SIZE));
}

t_env	*search(t_env **env_var, char *key)
{
	int		i;
	t_env	*tmp;

	i = hash(key);
	if (env_var[i])
	{
		tmp = env_var[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->key, key) == 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

char	*search_value(t_env **env_var, char *key)
{
	int		i;
	t_env	*tmp;

	i = hash(key);
	if (env_var[i])
	{
		tmp = env_var[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->key, key) == 0)
				return (tmp->value);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int	update_key(t_env **env_var, char *key, char *value)
{
	int		i;
	t_env	*tmp;

	i = hash(key);
	if (!value)
		value = "";
	if (env_var[i])
	{
		tmp = env_var[i];
		while (tmp)
		{
			if (strcmp(tmp->key, key) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

void	print_hashtable(t_env **env_var, int fd)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (env_var[i])
		{
			tmp = env_var[i];
			while (tmp)
			{
				ft_putstr_fd(tmp->key, fd);
				ft_putchar_fd('=', fd);
				ft_putendl_fd(tmp->value, fd);
				tmp = tmp->next;
			}
		}
		i++;
	}
}
