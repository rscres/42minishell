/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:59:28 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/02 16:20:02 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

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

int	main(void)
{
	t_env	*env_var[TABLE_SIZE];
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		env_var[i] = NULL;
		i++;
	}
	insert_key(env_var, "PATH", "/bin");
	insert_key(env_var, "BIN", "/usr/bin");
	insert_key(env_var, "LOCAL", "/usr/local/bin");
	insert_key(env_var, "SBIN", "/sbin");
	insert_key(env_var, "PATH", "/usr/sbin");
	insert_key(env_var, "LOCALS", "/usr/local/sbin");
	insert_key(env_var, "X11", "/opt/X11/bin");
	insert_key(env_var, "TEXBIN", "/usr/texbin");
	insert_key(env_var, "MUNKI", "/usr/local/munki");
	insert_key(env_var, "GIT", "/usr/local/git/bin");
	insert_key(env_var, "MYSQL", "/usr/local/mysql/bin");
	print_hashtable(env_var);

}
