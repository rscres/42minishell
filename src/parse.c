/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/14 19:23:57 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (*token == '\'' || *(token + ft_strlen(token) - 1) == '\'')
		tmp = ft_strtrim(token, "\'");
	else if (*token == '\"' || *(token + ft_strlen(token) - 1) == '\"')
		tmp = ft_strtrim(token, "\"");
	else
		tmp = ft_strdup(token);
	free(token);
	return (tmp);
}

int	parse_line(char **str)
{
	char	*token;
	char	*trim;

	token = tokenizer(*str);
	while (token)
	{
		trim = trim_quotes(token);
		add_token(trim, get_type(trim));
		free(trim);
		token = tokenizer(NULL);
	}
	if (g_main.open_quote)
	{
		ft_putstr_fd("Error: unclosed quotes\n", 2);
		clear_tokens();
		return (1);
	}
	clear_tokens(); //remove this later
	if (token)
		free(token);
	return (0);
}

// int	parse_line(char **str)
// {
// 	char	*token;
// 	// char	*new_str;
// 	char	*trim;

// 	token = tokenizer(*str);
// 	while (token)
// 	{
// 		trim = trim_quotes(token);
// 		add_token(trim, get_type(trim));
// 		free(trim);
// 		token = tokenizer(NULL);
// 	}
// 	//deal with open quotes-----------
// 	// while (g_main.open_quote)
// 	// {
// 	// 	new_str = readline("> ");
// 	// 	token = tokenizer(new_str);
// 	// 	while (token)
// 	// 	{
// 	// 		trim = trim_quotes(token);
// 	// 		add_token(trim, get_type(trim));
// 	// 		free(trim);
// 	// 		token = tokenizer(NULL);
// 	// 	}
// 	// 	*str = ft_strjoin(*str, "\n");
// 	// 	*str = ft_strjoin(*str, new_str);
// 	// 	free(new_str);
// 	// }
// 	//-----------------------------------
// 	// t_token	*tmp = g_main.tokens;
// 	// while (tmp)
// 	// {
// 	// 	printf("%s=>", tmp->name);
// 	// 	printf("%i\n", tmp->type);
// 	// 	tmp = tmp->next;
// 	// }
// 	clear_tokens();
// 	if (token)
// 		free(token);
// 	return (0);
// }