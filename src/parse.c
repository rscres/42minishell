/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/13 19:30:12 by rseelaen         ###   ########.fr       */
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
	// free(name);
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
	char	*tmp;

	if (!token)
		return (NULL);
	tmp = ft_strdup(token);
	if (*token == '\'' || *(token + ft_strlen(token) - 1) == '\'')
		tmp = ft_strtrim(token, "\'");
	else if (*token == '\"' || *(token + ft_strlen(token) - 1) == '\"')
		tmp = ft_strtrim(token, "\"");
	free(token);
	return (tmp);
}

int	parse_line(char **str)
{
	char	*token;
	char	*new_str;
	char	*trim;

	token = tokenizer(*str);
	while (token)
	{
		trim = trim_quotes(token);
		add_token(trim, get_type(trim));
		free(trim);
		token = tokenizer(NULL);
	}
	while (g_main.open_quote)
	{
		new_str = readline("> ");
		token = tokenizer(new_str);
		while (token)
		{
			trim = trim_quotes(token);
			add_token(trim, get_type(trim));
			free(trim);
			token = tokenizer(NULL);
		}
		*str = ft_strjoin(*str, "\n");
		*str = ft_strjoin(*str, new_str);
		free(new_str);
	}
	t_token	*tmp = g_main.tokens;
	while (tmp)
	{
		printf("%s=>", tmp->name);
		printf("%i\n", tmp->type);
		tmp = tmp->next;
	}
	clear_tokens();
	if (token)
		free(token);
	return (0);
}
