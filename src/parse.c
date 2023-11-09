/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/09 18:18:31 by rseelaen         ###   ########.fr       */
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

int	get_type(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (DOUBLE_GREATER_THAN);
	else if (!ft_strcmp(str, "<<"))
		return (DOUBLE_LESS_THAN);
	else if (!ft_strcmp(str, ">"))
		return (GREATER_THAN);
	else if (!ft_strcmp(str, "<"))
		return (LESS_THAN);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (WORD);
}

char	*trim_quotes(char *token)
{
	// char	*tmp;

	if (!token)
		return (NULL);
	// tmp = NULL;
	if (*token == '\'')
		token = ft_strtrim(token, "\'");
	else if (*token == '\"')
		token = ft_strtrim(token, "\"");
	return (token);
}

int	parse_line(char *str)
{
	char	*token;

	token = tokenizer(str);
	while (token)
	{
		add_token(trim_quotes(token), get_type(token));
		free(token);
		token = tokenizer(NULL);
	}
	t_token	*tmp = g_main.tokens;
	while (tmp)
	{
		printf("%s=>", tmp->name);
		printf("%i\n", tmp->type);
		tmp = tmp->next;
	}
	clear_tokens();
	while (g_main.tokens)
	{
		printf("%s=>", g_main.tokens->name);
		printf("%i\n", g_main.tokens->type);
		g_main.tokens = g_main.tokens->next;
	}
	if (token)
		free(token);
	return (0);
}
