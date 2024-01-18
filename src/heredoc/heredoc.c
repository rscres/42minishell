/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/18 00:28:28 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*expand_var_heredoc(char *str)
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

static void	*heredoc_error(char *delimiter, char *heredoc, int line_count)
{
	ft_safe_free((void **)&heredoc);
	ft_putstr_fd("heredoc: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	g_main.is_cmd_running = 0;
	g_main.status = 0;
	return (NULL);
}

static void	save_heredoc(char *delim, char *heredoc)
{
	int		fd;

	fd = open("./heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, heredoc, ft_strlen(heredoc) - ft_strlen(delim) - 1);
	close(fd);
	// fd = open("./heredoc", O_RDONLY);
	// dup2(fd, 0);
	// close(fd);
}

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*heredoc;
	int		line_count;

	g_main.is_cmd_running = 1;
	heredoc = ft_strdup("");
	line_count = 0;
	while (1)
	{
		line_count++;
		line = readline("> ");
		if (!line)
			return (heredoc_error(delimiter, heredoc, line_count));
		heredoc = ft_strjoin_free(heredoc, line);
		heredoc = ft_strjoin_free(heredoc, "\n");
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_safe_free((void **)&line);
	}
	save_heredoc(delimiter, heredoc);
	g_main.line = ft_strjoin_free(g_main.line, "\n");
	g_main.line = ft_strjoin_free(g_main.line, heredoc);
	heredoc = expand_var_heredoc(heredoc);
	g_main.is_cmd_running = 0;
	return (heredoc);
}
