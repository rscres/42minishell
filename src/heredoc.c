/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/28 13:57:55 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expand_var_heredoc(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			str = expand_var2(str, i);
	}
	return (str);
}

void	*heredoc_error(char *delimiter, char *heredoc, int line_count)
{
	ft_safe_free((void **)&heredoc);
	ft_putstr_fd("heredoc: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	g_main.is_heredoc_running = 0;
	g_main.status = 0;
	return (NULL);
}

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*tmp;
	char	*heredoc;
	int		line_count;

	g_main.is_heredoc_running = 1;
	heredoc = ft_strdup("");
	line_count = 0;
	while (1)
	{
		line_count++;
		line = readline("> ");
		if (!line)
			return (heredoc_error(delimiter, heredoc, line_count));
		if (!ft_strcmp(line, delimiter))
			break ;
		tmp = ft_strjoin(heredoc, line);
		free(heredoc);
		heredoc = ft_strjoin(tmp, "\n");
		ft_safe_free((void **)&tmp);
		ft_safe_free((void **)&line);
	}
	ft_safe_free((void **)&line);
	// g_main.line = ft_strjoin(line, heredoc);
	// printf("g_main.line: %s\n", g_main.line);
	heredoc = expand_var_heredoc(heredoc);
	printf("%s\n", heredoc);
	g_main.is_heredoc_running = 0;
	return (heredoc);
}
