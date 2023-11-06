/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:50 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/06 18:59:18 by rseelaen         ###   ########.fr       */
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
	j = i;
	while (save[j] && !ft_iswhitespace(save[j]))
		j++;
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

// int main(void)
// {
// 	char	*line;
// 	char	*token;

// 	line = get_line();
// 	while (line)
// 	{
// 		token = tokenizer(line);
// 		while (token)
// 		{
// 			printf("%s\n", token);
// 			free(token);
// 			token = tokenizer(NULL);
// 		}
// 		free(line);
// 		line = get_line();
// 	}
// 	return (0);
// }