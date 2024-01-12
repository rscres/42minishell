/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:50 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/27 14:16:37 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//The update_save function is used to update the static variable save.
//It is used to save the remaining string after the token has been extracted.
//It receives the current save and the index of the last character of the token
static char	*update_save(char *save, int i)
{
	char	*tmp;

	tmp = ft_strdup(save + i);
	free(save);
	return (tmp);
}

//The is_separator function is used to check if the current character is a
//separator(|, <, >). It returns 1 if it is and 0 if it isn't.
static int	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

//The check_quote function is used to check if quotes are open or closed. 
//And the type of quotes. It receives the current quote status:
//0 for closed or no quotes, 1 for open '\'' and 2 for open '\"', and the 
//current character. And returns the new quote status.
int	check_quote(int quote, char c)
{
	if (quote == 0 && c == '\'')
		return (1);
	else if (quote == 0 && c == '\"')
		return (2);
	else if (quote == 1 && c == '\'')
		return (0);
	else if (quote == 2 && c == '\"')
		return (0);
	return (quote);
}

//The get_j function is used to get the index of the last character of the
//token. It receives the index of the first character of the token and the
//current save string. It returns the index of the last character of the token.
static int	get_j(int i, char *save)
{
	int	j;
	int	quote;

	j = i;
	quote = g_main.open_quote;
	while (save[j])
	{
		if (save[j] == '\'' || save[j] == '\"')
			quote = check_quote(quote, save[j]);
		if (is_separator(save[j]) && !quote)
		{
			if ((save[j] == '<' && save[j + 1] == '<')
				|| (save[j] == '>' && save[j + 1] == '>'))
				j += 2;
			else if (save[j] == '<' || save[j] == '>' || save[j] == '|')
				j++;
			break ;
		}
		j++;
		if ((is_separator(save[j]) || ft_iswhitespace(save[j])) && !quote)
			break ;
	}
	g_main.open_quote = quote;
	return (j);
}

//The tokenizer function is used to split the input into tokens.
//It is my own implementation of the strtok function and it works similarly.
//When first called it takes the input string and saves it in a static variable.
//All subsequent calls to the function will use the static variable instead of 
//the input string.
char	*tokenizer(char *str)
{
	static char	*save;
	char		*token;
	int			i;
	int			j;

	i = 0;
	if (str)
		save = ft_strdup(str);
	while (save[i] && ft_iswhitespace(save[i]))
		i++;
	if (save[i] == '\0')
	{
		if (save)
			free(save);
		return (NULL);
	}
	j = get_j(i, save);
	token = ft_strndup(save + i, j - i);
	save = update_save(save, j);
	return (token);
}
