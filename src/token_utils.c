/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:23:01 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/14 19:23:49 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*new_token(char *name, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->name = ft_strdup(name);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(char *name, int type)
{
	t_token	*tmp;

	if (g_main.tokens == NULL)
	{
		g_main.tokens = new_token(name, type);
		return ;
	}
	tmp = g_main.tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token(name, type);
	tmp->next->prev = tmp;
}

void	clear_tokens(void)
{
	t_token	*tmp;

	while (g_main.tokens)
	{
		tmp = g_main.tokens;
		g_main.tokens = g_main.tokens->next;
		free(tmp->name);
		free(tmp);
	}
}