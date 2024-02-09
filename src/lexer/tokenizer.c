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

#include "../../includes/shell.h"

static char	*update_save(char *save, int i)
{
	char	*tmp;

	tmp = ft_strdup(save + i);
	free(save);
	return (tmp);
}

static int	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

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
