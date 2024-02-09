/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:09:27 by renato            #+#    #+#             */
/*   Updated: 2024/02/05 22:28:36 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (!value)
		value = "";
	if (env_var[i] == NULL)
	{
		env_var[i] = (t_env *)malloc(sizeof(t_env));
		env_var[i]->key = ft_strdup(key);
		env_var[i]->value = ft_strdup(value);
		env_var[i]->next = NULL;
	}
	else
	{
		tmp = env_var[i];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->key = ft_strdup(key);
		tmp->next->value = ft_strdup(value);
		tmp->next->next = NULL;
	}
}

void	delete_key(t_env **env_var, char *key)
{
	int		i;
	t_env	*current;
	t_env	*hold;

	i = hash(key);
	current = env_var[i];
	hold = NULL;
	while (current != NULL && strcmp(current->key, key) != 0)
	{
		hold = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (hold == NULL)
		env_var[i] = current->next;
	else
		hold->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
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
