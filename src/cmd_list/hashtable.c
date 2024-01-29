/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:59:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/29 16:08:49 by rseelaen         ###   ########.fr       */
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

//The insert_key receives the hashtable ,and a key and value as strings.
//It calculates the hash value of the key and inserts the key and value
//into the hashtable at the index of the hash value.
//If the index is already occupied, it will insert the key and value at the
//end of the linked list.
//Otherwise, it will just add the key and value to the hashtable.
void	insert_key(t_env **env_var, char *key, char *value)
{
	int		i;
	t_env	*tmp;

	i = hash(key);
	if (env_var[i] == NULL)
	{
		env_var[i] = (t_env *)malloc(sizeof(t_env));
		env_var[i]->key = strdup(key);
		env_var[i]->value = strdup(value);
		env_var[i]->next = NULL;
	}
	else
	{
		tmp = env_var[i];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->key = strdup(key);
		tmp->next->value = strdup(value);
		tmp->next->next = NULL;
	}
}

void	delete_key(t_env **env_var, char *key)
{
	int		i;
	t_env	*tmp;
	t_env	*next;

	i = hash(key);
	if (env_var[i])
	{
		tmp = env_var[i];
		while (tmp)
		{
			next = tmp->next;
			if (strcmp(tmp->key, key) == 0)
			{
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				env_var[i] = next;
				break ;
			}
			tmp = next;
		}
	}
}

void	clear_hashtable(t_env **env_var)
{
	int		i;
	t_env	*tmp;
	t_env	*next;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (env_var[i])
		{
			tmp = env_var[i];
			while (tmp)
			{
				next = tmp->next;
				ft_safe_free((void **)&tmp->key);
				ft_safe_free((void **)&tmp->value);
				ft_safe_free((void **)&tmp);
				tmp = next;
			}
		}
		i++;
	}
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
			if (strcmp(tmp->key, key) == 0)
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
			if (strcmp(tmp->key, key) == 0)
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
	if (env_var[i])
	{
		tmp = env_var[i];
		while (tmp)
		{
			if (strcmp(tmp->key, key) == 0)
			{
				free(tmp->value);
				tmp->value = strdup(value);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

//For testing purposes-----------------------------------------
void	print_hashtable(t_env **env_var)
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
				printf("%s", tmp->key);
				printf("=");
				printf("%s", tmp->value);
				printf("\n");
				tmp = tmp->next;
			}
		}
		i++;
	}
}
