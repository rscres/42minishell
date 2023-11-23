/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/23 14:07:20 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*tmp;
	char	*heredoc;

	heredoc = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delimiter))
			break ;
		tmp = ft_strjoin(heredoc, line);
		free(heredoc);
		heredoc = ft_strjoin(tmp, "\n");
		free(tmp);
		free(line);
	}
	free(line);
	return (heredoc);
}
