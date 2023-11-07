/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:50 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/07 16:39:08 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

static int	get_j(int i, char *save)
{
	int j;
	
	j = i;
	while (save[j] && !ft_iswhitespace(save[j]))
	{
		if (is_separator(save[j]))
		{
			if ((save[j] == '<' && save[j + 1] == '<')
				|| (save[j] == '>' && save[j + 1] == '>'))
				j += 2;
			else if (save[j] == '<' || save[j] == '>' || save[j] == '|')
				j++;
			break ;
		}
		j++;
		if (is_separator(save[j]))
			break ;
	}
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

int	parse_line(char *str)
{
	char	*token;

	token = tokenizer(str);
	while (token)
	{
		printf("%s\n", token);
		free(token);
		token = tokenizer(NULL);
	}
	return (0);
}
